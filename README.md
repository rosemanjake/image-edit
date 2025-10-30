# Image Editor

This is a basic image editing program. I wrote it just to practice my C skills
while on paternity leave. It is **not** vibe coded. The use of AI was limited to
unblocking errors; the implementation is my own.

## Transformations

This program supports Bitmap files. The possible transformations are as follows:

-   Vertical flip.
-   Horizontal flip.
-   Fill with solid color (blue).

## Compile

Compile the program with this `gcc` command:

```shell
gcc -Wall -Wextra -g3 \
    /path/to/imageeditor.c \
    /path/to/commandinfo.c \
    /path/to/imagedata.c \
    /path/to/imagetransforms.c \
    -o /path/to/output/imageeditor
```

## Run

Run the binary from the command line and pass it 3 arguments:

1. The requested transform:
    1. `vertical_flip`
    2. `horizontal_flip`
    3. `solid_color`
2. The absolute path to the input file.
3. The absolute path to the output file.

Your command may look as follows:

```shell
./imageeditor vertical_flip \
    /path/to/file/my_image.bmp \
    /path/to/file/my_output_image.bmp
```

## Performance

For a 5MB BMP image on my Macbook Air M2, the processing times are as follows:

-   `horizontal_flip`: 11.73ms.
-   `vertical_flip`: 2.2ms.
-   `solid_color`: 6.0ms.

In my first attempt, the program was running in ~27ms. This was because I was
arranging the pixel data into a 2D array to make the transformation functions
simpler. However, that approach was quite slow because the program was copying
the data multiple time across several buffers.

I simplified the code so that it copies data from the file buffer directly into
a single output buffer, using `memcpy` and `memset` where possible. Doing so
yields a much faster program.
