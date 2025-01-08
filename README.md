## Proof of concept for generating a high-resolution video with raw binary image files piped to ffmpeg

### Using specific flags to get ffmpeg into a mode where it reads binary bytes of frames in RGB32 and assembles them into a video in real-time

### Idea: ffmpeg should be started as a child_process by the program together with a pipe where it gets fed raw data from the program. Ffmpeg then outputs assembled video.
