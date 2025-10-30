# Image Editor

This is a basic image editing program. I wrote it just to practice my C skills.
It is **not** vibe coded. The use of AI was limited to unblocking errors; the
implementation is my own.

## Transformations

This program supports Bitmap files. The possible transformations are as follows:

-   Vertical flip.
-   Horizontal flip.
-   Fill with solid color (blue).

## Compile

Compile the program with this `gcc` command:

```shell
gcc -Wall -Wextra -g3 /Users/jakeroseman/image-edit/imageeditor.c /Users/jakeroseman/image-edit/commandinfo.c /Users/jakeroseman/image-edit/imagemetadata.c /Users/jakeroseman/image-edit/imagetransforms.c -o /Users/jakeroseman/image-edit/output/imageeditor
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
./"imageeditor" vertical_flip /path/to/file/my_image.bmp /path/to/file/my_output_image.bmp
```
