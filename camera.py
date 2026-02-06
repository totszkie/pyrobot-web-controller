import cv2

class VideoCamera:
    def __init__(self):
        self.video = cv2.VideoCapture(1)
        # Set base resolution to 1080p (1920x1080)
        # OpenCV will automatically adjust to the closest supported resolution
        # if the hardware does not support exactly 1080p.
        self.video.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
        self.video.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

    def __del__(self):
        self.video.release()

    def get_frame(self):
        success, image = self.video.read()
        if not success:
            return None
        
        ret, jpeg = cv2.imencode('.jpg', image)
        return jpeg.tobytes()

def gen(camera):
    while True:
        frame = camera.get_frame()
        if frame:
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')