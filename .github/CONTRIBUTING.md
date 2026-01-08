# Contributing to Collision Detection for Drones

Thank you for your interest in contributing! This document provides guidelines and instructions for contributing to this project.

---

## Table of Contents

- [Getting Started](#getting-started)
- [Development Setup](#development-setup)
- [Code Style](#code-style)
- [Testing](#testing)
- [Pull Request Process](#pull-request-process)
- [Project Structure](#project-structure)
- [Common Tasks](#common-tasks)

---

## Getting Started

### Prerequisites

- **Python 3.8+** for Flask backend
- **Node.js 14+** (optional, for linting)
- **Arduino IDE** or **Arduino CLI** for firmware
- **ROS** (Robot Operating System) for integration
- **Git** for version control

### Quick Start

```bash
# Clone the repository
git clone https://github.com/dronefreak/collision-detection-for-drones.git
cd collision-detection-for-drones

# Install Python dependencies
pip install -r requirements.txt

# Install development tools
pip install black flake8 pytest pytest-flask

# Run linters
flake8 flytsonar/
black --check flytsonar/

# Run tests
pytest tests/
```

---

## Development Setup

### 1. Fork and Clone

```bash
# Fork the repository on GitHub, then:
git clone https://github.com/YOUR_USERNAME/collision-detection-for-drones.git
cd collision-detection-for-drones

# Add upstream remote
git remote add upstream https://github.com/dronefreak/collision-detection-for-drones.git
```

### 2. Create a Branch

```bash
# Create a feature branch
git checkout -b feature/your-feature-name

# Or a bugfix branch
git checkout -b fix/issue-number-description
```

### 3. Make Changes

- Write clean, well-documented code
- Follow the code style guidelines below
- Add tests for new functionality
- Update documentation as needed

### 4. Test Your Changes

```bash
# Run Python linters
flake8 flytsonar/
black --check flytsonar/

# Run JavaScript linter
eslint flytsonar/static/js/index.js

# Run tests
pytest tests/

# Test manually with hardware/simulator
```

---

## Code Style

### Python

- **Style**: Follow [PEP 8](https://pep8.org/)
- **Formatter**: Use [Black](https://black.readthedocs.io/) with 88-character line length
- **Linter**: Use [flake8](https://flake8.pycqa.org/)

```bash
# Auto-format Python code
black flytsonar/

# Check style
flake8 flytsonar/
```

**Example:**
```python
def add_security_headers(response):
    """Add security headers to all responses"""
    response.headers["Content-Security-Policy"] = (
        "default-src 'self'; "
        "script-src 'self' 'unsafe-inline';"
    )
    return response
```

### JavaScript

- **Style**: ES5 syntax for compatibility
- **Linter**: ESLint (see `.eslintrc.json`)
- **Indentation**: 2 spaces
- **Semicolons**: Required

```bash
# Check JavaScript style
eslint flytsonar/static/js/index.js

# Auto-fix issues
eslint --fix flytsonar/static/js/index.js
```

**Example:**
```javascript
/**
 * Validate a number within a range
 * @param {number} value - Value to validate
 * @param {number} min - Minimum allowed value
 * @param {number} max - Maximum allowed value
 * @param {number} defaultValue - Default if invalid
 * @returns {number} Validated value
 */
function validateNumber(value, min, max, defaultValue) {
  var num = parseFloat(value);
  if (isNaN(num) || num < min || num > max) {
    return defaultValue;
  }
  return num;
}
```

### Arduino/C++

- **Style**: Follow [Arduino Style Guide](https://www.arduino.cc/en/Reference/StyleGuide)
- **Indentation**: 2 spaces
- **Comments**: Use `//` for single-line, `/* */` for multi-line

**Example:**
```cpp
// Initialize sonar sensor array
for (uint8_t i = 0; i < SONAR_NUM; i++) {
  sonar_data[i] = 0;
}
```

### HTML/CSS

- **Indentation**: 4 spaces (HTML), 2 spaces (CSS)
- **Format**: Use EditorConfig for consistency

---

## Testing

### Python Tests

Location: `tests/test_flask_app.py`

```bash
# Run all tests
pytest tests/

# Run with coverage
pytest tests/ --cov=flytsonar --cov-report=html

# Run specific test
pytest tests/test_flask_app.py::test_security_headers
```

**Writing Tests:**
```python
def test_security_headers(client):
    """Test that security headers are present"""
    response = client.get('/')
    assert 'X-Frame-Options' in response.headers
    assert response.headers['X-Frame-Options'] == 'SAMEORIGIN'
```

### JavaScript Tests

Location: `tests/test_validation.js`

```bash
# Install Jest (if not installed)
npm install --save-dev jest

# Run tests
npm test
```

**Writing Tests:**
```javascript
describe('validateNumber', () => {
  test('returns number within range', () => {
    expect(validateNumber(5, 0, 10, 0)).toBe(5);
  });
});
```

### Arduino Tests

- Use [ArduinoUnit](https://github.com/mmurdoch/arduinounit) or similar
- Test on actual hardware when possible
- Verify no memory leaks with extended runtime tests

---

## Pull Request Process

### 1. Update Your Branch

```bash
# Fetch latest changes from upstream
git fetch upstream
git rebase upstream/main
```

### 2. Commit Your Changes

```bash
# Stage changes
git add .

# Commit with descriptive message
git commit -m "Add feature: detailed description

- First change
- Second change
- Fixes #issue-number"
```

**Commit Message Guidelines:**
- Use imperative mood ("Add feature" not "Added feature")
- First line: brief summary (50 characters or less)
- Blank line, then detailed description
- Reference issues: "Fixes #123" or "Relates to #456"

### 3. Push to Your Fork

```bash
git push origin feature/your-feature-name
```

### 4. Create Pull Request

1. Go to GitHub and create a Pull Request
2. Fill out the PR template
3. Link related issues
4. Wait for CI checks to pass
5. Respond to review comments

### 5. After Approval

- Maintainers will merge your PR
- Delete your feature branch
- Pull latest changes from upstream

---

## Project Structure

```
collision-detection-for-drones/
├── arduino/
│   ├── sonar_jig_6.ino          # Arduino firmware
│   └── libraries/                # Required libraries
├── flytsonar/
│   ├── __init__.py               # Package initialization
│   ├── views.py                  # Flask routes & security headers
│   └── static/
│       ├── index.html            # Main web interface
│       ├── js/
│       │   └── index.js          # Main application logic
│       ├── css/                  # Stylesheets
│       └── images/               # UI assets
├── tests/
│   ├── test_flask_app.py         # Python tests
│   └── test_validation.js        # JavaScript tests
├── STL_files/                    # 3D-printable mounts
├── .github/
│   └── workflows/
│       └── ci.yml                # GitHub Actions CI/CD
├── .gitignore                    # Git ignore patterns
├── .eslintrc.json                # JavaScript linting rules
├── .editorconfig                 # Editor configuration
├── requirements.txt              # Python dependencies
├── package.json                  # JavaScript dependencies
├── README.md                     # Project documentation
└── CONTRIBUTING.md               # This file
```

---

## Common Tasks

### Add a New ROS Topic Listener

```javascript
var listenerNewTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/topic_name',
  messageType: 'std_msgs/String'
});

listenerNewTopic.subscribe(function(message) {
  console.log('Received:', message.data);
  // Handle message
});
```

### Add a New Flask Route

```python
@flytsonar.route('/new-route')
def new_route():
    """Handle new route"""
    # Your logic here
    return make_response('Response')
```

### Add Input Validation

```javascript
// Use existing validation functions
var validatedRate = validateInteger(
  userInput,
  1,    // min
  200,  // max
  40    // default
);
```

### Update Arduino Sensor Logic

```cpp
// Add new sensor
#define SONAR_NUM 7  // Update count

NewPing sonarSENSOR[SONAR_NUM] = {
  // ... existing sensors
  NewPing(14, 8, MAX_DISTANCE)  // New sensor
};
```

---

## Documentation

### Adding JSDoc Comments

```javascript
/**
 * Brief description of function
 *
 * Detailed description if needed.
 *
 * @param {type} paramName - Parameter description
 * @returns {type} Return value description
 * @throws {Error} When something goes wrong
 * @example
 * // Usage example
 * myFunction(arg1, arg2);
 */
function myFunction(paramName) {
  // Implementation
}
```

### Adding Python Docstrings

```python
def my_function(param):
    """
    Brief description.

    Detailed description if needed.

    Args:
        param (type): Parameter description

    Returns:
        type: Return value description

    Raises:
        ValueError: When something is invalid
    """
    pass
```

---

## Troubleshooting

### CI Checks Failing

```bash
# Run checks locally before pushing
flake8 flytsonar/
black --check flytsonar/
eslint flytsonar/static/js/index.js
pytest tests/
```

### Merge Conflicts

```bash
# Update your branch
git fetch upstream
git rebase upstream/main

# Resolve conflicts
# Edit conflicting files
git add .
git rebase --continue
```

### EditorConfig Not Working

- Install EditorConfig plugin for your editor
- VS Code: "EditorConfig for VS Code"
- IntelliJ: Built-in support
- Check `.editorconfig` file is in project root

---

## Code Review Guidelines

### For Contributors

- Keep PRs focused and small
- Write clear commit messages
- Add tests for new features
- Update documentation
- Respond promptly to feedback

### For Reviewers

- Be constructive and respectful
- Focus on code quality, not style (linters handle that)
- Suggest improvements, don't demand perfection
- Approve once CI passes and code looks good

---

## Resources

- [Project README](README.md)
- [Phase 1 Changes](PHASE1_CHANGES.md) - Bug fixes
- [Phase 2 Changes](PHASE2_CHANGES.md) - Dependency updates
- [Phase 3 Changes](PHASE3_CHANGES.md) - CI/CD setup
- [Library Update Guide](LIBRARY_UPDATE_GUIDE.md)

**External Resources:**
- [FlytOS Documentation](https://docs.flytbase.com/)
- [ROS Tutorials](http://wiki.ros.org/ROS/Tutorials)
- [roslibjs API](http://robotwebtools.org/jsdoc/roslibjs/)
- [Flask Documentation](https://flask.palletsprojects.com/)
- [Arduino Reference](https://www.arduino.cc/reference/en/)

---

## Getting Help

- **Issues**: Open an issue on GitHub
- **Discussions**: Use GitHub Discussions
- **Email**: Contact maintainers (see README)

---

## License

By contributing, you agree that your contributions will be licensed under the same license as the project (see LICENSE file).

---

Thank you for contributing! 🚀
