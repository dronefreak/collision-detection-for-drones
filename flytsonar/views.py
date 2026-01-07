from flask import Blueprint, render_template, make_response

flytsonar = Blueprint('flytsonar', __name__, static_folder='static')


def add_security_headers(response):
    """Add security headers to all responses"""
    # Content Security Policy - adjust based on your needs
    # Note: 'unsafe-inline' and 'unsafe-eval' are needed for current inline scripts
    # TODO: Move inline scripts to separate files and remove unsafe-* directives
    response.headers['Content-Security-Policy'] = (
        "default-src 'self'; "
        "script-src 'self' 'unsafe-inline' 'unsafe-eval' https://oss.maxcdn.com; "
        "style-src 'self' 'unsafe-inline'; "
        "img-src 'self' data: http: https:; "
        "font-src 'self' data:; "
        "connect-src 'self' ws: wss:;"
    )

    # Prevent clickjacking
    response.headers['X-Frame-Options'] = 'SAMEORIGIN'

    # Prevent MIME type sniffing
    response.headers['X-Content-Type-Options'] = 'nosniff'

    # Enable XSS protection (for older browsers)
    response.headers['X-XSS-Protection'] = '1; mode=block'

    # Referrer policy
    response.headers['Referrer-Policy'] = 'strict-origin-when-cross-origin'

    # Permissions policy (formerly Feature-Policy)
    response.headers['Permissions-Policy'] = (
        'geolocation=(), '
        'microphone=(), '
        'camera=()'
    )

    return response


@flytsonar.after_request
def after_request(response):
    """Add security headers to all responses"""
    return add_security_headers(response)


@flytsonar.route('/')
def timeline():
    """Serve the main index page"""
    response = make_response(flytsonar.send_static_file('index.html'))
    return response


@flytsonar.route('/<path:path>')
def remfiles(path):
    """Serve static files with security headers"""
    # Basic path validation to prevent directory traversal
    if '..' in path or path.startswith('/'):
        return "Invalid path", 400

    try:
        response = make_response(flytsonar.send_static_file(path))
        return response
    except Exception as e:
        return f"File not found: {path}", 404

