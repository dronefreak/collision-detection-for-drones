#include <ros.h>
#include <std_msgs/Int32MultiArray.h>
#include <NewPing.h>
#define SONAR_NUM 6
#define MAX_DISTANCE 200
#define PING_INTERVAL 35
#define MIN_DATA_RATE 1
#define MAX_DATA_RATE 200
#define DEFAULT_DATA_RATE 100

ros::NodeHandle nh;
int i, ros_array[6] = {1,1,1,1,1,1};
float data_rate = DEFAULT_DATA_RATE;
float data_rate_inv;
char dim0_label[] = "sonar";
unsigned long pingTimer[SONAR_NUM];
long cm[SONAR_NUM];
uint8_t currentSensor = 0;

// Static allocation for message data - no malloc/free needed
int32_t sonar_data[SONAR_NUM];
std_msgs::MultiArrayDimension sonar_dim[1];

void messageCb(const std_msgs::Int32MultiArray& msg){
  // Input validation for data_rate
  if(msg.data[0] >= MIN_DATA_RATE && msg.data[0] <= MAX_DATA_RATE) {
    data_rate = msg.data[0];
    data_rate_inv = (1.0/data_rate)*1000.0;
  }

  // Validate sensor enable/disable values (0 or 1)
  if(msg.data[1] == 0 || msg.data[1] == 1) ros_array[4] = msg.data[1];
  if(msg.data[2] == 0 || msg.data[2] == 1) ros_array[5] = msg.data[2];
  if(msg.data[3] == 0 || msg.data[3] == 1) ros_array[2] = msg.data[3];
  if(msg.data[4] == 0 || msg.data[4] == 1) ros_array[3] = msg.data[4];
}

std_msgs::Int32MultiArray sonar;
ros::Publisher sonar_pub("sonar", &sonar);
ros::Subscriber<std_msgs::Int32MultiArray> sensors("msg", &messageCb);

NewPing sonarSENSOR[SONAR_NUM] = {
  NewPing(9, 2, MAX_DISTANCE),
  NewPing(8, 3, MAX_DISTANCE),
  NewPing(11, 6, MAX_DISTANCE),
  NewPing(10, 7, MAX_DISTANCE),
  NewPing(13, 4, MAX_DISTANCE),
  NewPing(12, 5, MAX_DISTANCE)
};

void setup() {
  pingTimer[0] = millis() + 75;
  for (uint8_t i = 1; i < SONAR_NUM; i++) {
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
  }

  nh.initNode();

  // Use static allocation instead of malloc - no memory leak
  sonar.data_length = SONAR_NUM;
  sonar.layout.dim = sonar_dim;
  sonar.layout.dim_length = 1;
  sonar.layout.dim[0].label = dim0_label;
  sonar.layout.dim[0].size = SONAR_NUM;
  sonar.layout.dim[0].stride = SONAR_NUM;
  sonar.layout.data_offset = 0;
  sonar.data = sonar_data;

  // Initialize data array
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    sonar_data[i] = 0;
  }

  // Calculate initial data_rate_inv
  data_rate_inv = (1.0/data_rate)*1000.0;

  nh.advertise(sonar_pub);
  nh.subscribe(sensors);
}

void loop()
{
  for(uint8_t i = 0; i < SONAR_NUM; i++){
    if(ros_array[i]){
      if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
        pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
        if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle();
        sonarSENSOR[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
        currentSensor = i;                          // Sensor being accessed.
        sonarSENSOR[currentSensor].ping_timer(echoCheck);
      }
    }
    else{
      cm[i] = 400;  // Disabled sensor returns max distance
    }
  }

  // Copy data from cm array to sonar_data for publishing
  for(uint8_t i = 0; i < SONAR_NUM; i++){
    sonar_data[i] = cm[i];
  }

  sonar_pub.publish(&sonar);
  nh.spinOnce();

  // Safe delay with bounds checking
  if(data_rate_inv > 0) {
    delay(data_rate_inv);
  }
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonarSENSOR[currentSensor].check_timer())
    cm[currentSensor] = sonarSENSOR[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    sonar_data[i] = cm[i];
  }
}
