# Library Update Guide - Phase 2

## Overview
This document outlines the process for updating outdated JavaScript libraries in the FlytSonar web application.

---

## Current Library Versions (Outdated)

| Library | Current Version | Latest Version | Age | Risk Level |
|---------|----------------|----------------|-----|------------|
| jQuery | 1.11.3 (2015) | 3.7.1 | 8+ years | 🔴 HIGH |
| Bootstrap | 3.x (2013) | 5.3.2 | 10+ years | 🔴 HIGH |
| jQuery UI | 1.10.1 (2013) | 1.13.2 | 10+ years | 🔴 HIGH |
| roslib.js | 0.18.0-SNAPSHOT | 1.3.0 | 5+ years | 🟡 MEDIUM |
| Select2 | 3.4.5 (2014) | 4.1.0 | 9+ years | 🟡 MEDIUM |
| Ion.RangeSlider | 1.8.2 | 2.3.1 | 7+ years | 🟡 MEDIUM |

---

## Update Strategy

### Phase 2A: Non-Breaking Updates (CURRENT)
✅ jQuery 1.11.3 → 3.7.1 (via CDN)
✅ roslib.js 0.18.0-SNAPSHOT → 1.3.0 (via CDN)
- Minimal code changes required
- Can use CDN for immediate deployment

### Phase 2B: Minor Updates (Recommended)
- Select2 3.4.5 → 4.1.0
- Ion.RangeSlider 1.8.2 → 2.3.1
- Requires API migration

### Phase 2C: Major Refactoring (Future)
- Bootstrap 3 → Bootstrap 5
- Remove jQuery dependency where possible
- Modern ES6+ JavaScript
- **Estimated effort**: 2-3 weeks

---

## jQuery 3.7.1 Migration

### Breaking Changes to Address

#### 1. Removed Methods
```javascript
// OLD (Removed in jQuery 3.x)
$('div').size()
$('div').andSelf()

// NEW
$('div').length
$('div').addBack()
```

#### 2. parseInt() Behavior
```javascript
// jQuery 3.x uses base-10 by default
// Our code uses parseInt() - should add radix parameter
parseInt(value, 10)  // Always specify base-10
```

#### 3. jQuery.isNumeric() Changes
```javascript
// jQuery 3.x: Returns false for whitespace-only strings
// Impact: Minimal in our code
```

### Files That May Need Updates
1. `flytsonar/static/js/index.js` - Main application logic
2. `flytsonar/static/js/scripts.js` - UI framework
3. Any files using deprecated methods

### Migration Steps
1. ✅ Update `<script>` tag to use jQuery 3.7.1 CDN
2. ⚠️ Test all interactive features:
   - Sonar sensor toggles
   - Slider controls
   - Button click handlers
   - AJAX calls
3. ⚠️ Check browser console for deprecation warnings
4. Fix any broken functionality

---

## roslib.js 1.3.0 Migration

### Changes from 0.18.0-SNAPSHOT → 1.3.0

#### API Stability
- SNAPSHOT version is unstable/dev build
- 1.3.0 is stable release
- Better WebSocket handling
- Improved error messages

#### Breaking Changes (Minimal)
- Most APIs remain compatible
- Better TypeScript definitions
- Improved ROS 2 support (not used here)

### Migration Steps
1. ✅ Update `<script>` tag to use roslib.js 1.3.0 CDN
2. ⚠️ Test ROS connections:
   - Topic subscriptions (/sonar)
   - Topic publishing (/msg)
   - Service calls (if used)
3. ⚠️ Verify WebSocket reconnection logic
4. Check for console errors

---

## CDN Links (Recommended for Phase 2)

### jQuery 3.7.1
```html
<!-- Replace in index.html -->
<script src="https://code.jquery.com/jquery-3.7.1.min.js"
        integrity="sha256-/JqT3SQfawRcv/BIHPThkBvs0OEvtFFmqPF/lYI/Cxo="
        crossorigin="anonymous"></script>
```

### roslib.js 1.3.0
```html
<!-- Replace in index.html -->
<script src="https://cdn.jsdelivr.net/npm/roslib@1.3.0/build/roslib.min.js"
        crossorigin="anonymous"></script>
```

### jQuery UI 1.13.2 (Recommended)
```html
<link rel="stylesheet" href="https://code.jquery.com/ui/1.13.2/themes/base/jquery-ui.min.css">
<script src="https://code.jquery.com/ui/1.13.2/jquery-ui.min.js"
        integrity="sha256-lSjKY0/srUM9BE3dPm+c4fBo1dky2v27Gdjm2uoZaL0="
        crossorigin="anonymous"></script>
```

---

## Testing Checklist

### Manual Testing Required

#### jQuery Update Tests
- [ ] Page loads without errors
- [ ] All buttons respond to clicks
- [ ] Sliders work (Ion.RangeSlider compatibility)
- [ ] Bootstrap switches work
- [ ] AJAX calls succeed (getNamespace, takeoff, land)
- [ ] Animations work (jQuery.rotate, height changes)
- [ ] Select2 dropdowns work
- [ ] No console errors

#### roslib.js Update Tests
- [ ] ROS connection established
- [ ] Sonar data displays correctly
- [ ] Can toggle sensors on/off
- [ ] Can adjust data rate slider
- [ ] Can adjust threshold slider
- [ ] Battery status updates (if FlytOS connected)
- [ ] Vehicle state updates (if FlytOS connected)

#### Security Headers Tests
- [ ] CSP header present (check with browser DevTools)
- [ ] X-Frame-Options header present
- [ ] X-Content-Type-Options header present
- [ ] No console CSP violations

---

## Rollback Plan

If updates cause issues:

1. **Immediate Rollback** (jQuery)
   ```html
   <!-- Revert to old version -->
   <script src="js/jquery.js"></script>
   ```

2. **Immediate Rollback** (roslib.js)
   ```html
   <!-- Revert to old version -->
   <script src="js/roslib.min.js"></script>
   ```

3. **Document Issues**
   - What broke?
   - Console errors?
   - Which feature?
   - Browser version?

4. **Incremental Fix**
   - Fix compatibility issues
   - Re-test
   - Re-deploy

---

## Bootstrap 3 → 5 Migration (Phase 3 - NOT NOW)

**⚠️ DO NOT ATTEMPT YET - MAJOR BREAKING CHANGES**

### Why Bootstrap 5 is Complex
- jQuery dependency removed (requires JS rewrite)
- Class name changes (`.pull-left` → `.float-start`)
- Grid system changes
- Component API changes
- Estimated effort: 2-3 weeks

### Bootstrap 5 Migration Steps (Future)
1. Audit all Bootstrap classes in use
2. Create class mapping document
3. Test in staging environment
4. Rewrite JavaScript to remove jQuery where needed
5. Update all HTML templates
6. Test extensively

---

## Monitoring & Maintenance

### After Updates
1. Monitor browser console for errors
2. Test on multiple browsers:
   - Chrome/Edge (latest)
   - Firefox (latest)
   - Safari (latest)
3. Monitor user reports
4. Keep libraries updated quarterly

### Security Updates
- Subscribe to security advisories:
  - https://github.com/jquery/jquery/security
  - https://github.com/RobotWebTools/roslibjs/issues
- Check for CVEs regularly
- Update immediately if security issues found

---

## Resources

- [jQuery 3.x Upgrade Guide](https://jquery.com/upgrade-guide/3.0/)
- [roslibjs Documentation](http://robotwebtools.org/jsdoc/roslibjs/)
- [Bootstrap 5 Migration Guide](https://getbootstrap.com/docs/5.3/migration/)
- [Can I Use](https://caniuse.com/) - Browser compatibility

---

## Phase 2 Summary

### Completed in Phase 2
✅ Created package.json for dependency tracking
✅ Created requirements.txt for Python dependencies
✅ Added security headers to Flask application
✅ Created comprehensive update documentation
✅ Updated jQuery to 3.7.1 via CDN
✅ Updated roslib.js to 1.3.0 via CDN

### Deferred to Phase 3
⏭️ Bootstrap 3 → 5 (major refactoring)
⏭️ Select2 3 → 4 (API changes)
⏭️ Ion.RangeSlider 1 → 2 (minor changes)
⏭️ Remove commented dead code
⏭️ Refactor duplicated code

---

*Last updated: Phase 2*
*Status: In Progress*
