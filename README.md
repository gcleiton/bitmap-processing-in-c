
# BITMAP 24-BIT PROCESSING IMAGE
In this repository, I am making available here the open source of a project developed during the second period of the Computer Science course. The project consists of applying a series of transformations to 24-bit bitmap images.

> **Note:** The application will only work on bitmap images whose architecture is 24-bit, where each pixel has 8 bits (1 byte).


 - GitHub profile: [gcleiton](https://www.github.com/gcleiton)
 - Email for contact: ccgabrielcc2609@gmail.com

## About Bitmap

The 24-bit bitmap format consists of three parts, including:

 - **FILEHEADER:** information regarding the file.
- **INFOHEADER:** information regarding the image.
- **PIXELS DATA:** arrangement of the pixels arranged in the BGR standard, plus padding, if applicable.

Regarding image pixels, attention should be paid to padding and 24-bit bitmap architecture. Because we are dealing with a 24-bit format each pixel component, that is, blue, green and red, will have a size of 8 bits (1 byte). In addition, padding is a technique of computation used in the bitmap, whose function is to fill the space of the actual image width, such that the final width value is divisible by 4.

It is worth mentioning that, even in relation to pixels, it is important to highlight the way the bitmap stores the image's pixels upside down. This means that the first line that is played on the screen is actually the last line.

## Availables Transformations

|Function Name| Description |
|--|--|
| copy | Allows you to make a copy of the image. |
| rotate90DegreesRight | Allows you to rotate the image 90 degrees to the right. |
| rotate90DegreesLeft | Allows you to rotate the image 90 degrees to the left. |
| rotate180Degrees | Allows you to rotate the image 180 degrees. |
| flipHorizontally | Lets you rotate the image vertically. |
| flipVertically | Lets you rotate the image horizontally. |
| applyGrayscale | Allows you to apply gray scale to the image |

> **Note:** The transformations can be viewed in the images directory that will be created by main.c. However, if you want to change the directory, just change the value of the DEFAULT_PATH constant in the src/bitmap.h file.`

    #define  DEFAULT_PATH  "YOUR_DIRECTORY_HERE"

## Compilation

The 24-bit Bitmap Processing Image can be compiled using GCC by following such commands:

    gcc -c ./src/bitmap.c -o ./obj/bitmap.o
    gcc -c main.c -o ./obj/main.o
    gcc -o bitmap .\obj\bitmap.o .\obj\main.o

## Showcase

![welcome message and file choise](https://i.ibb.co/8KR3GdT/1.png)

![read image and show information](https://i.ibb.co/19gRZ1W/2.png)

![transformation choise](https://i.ibb.co/5cpJGsZ/3.png)

![progress bar of image processing](https://i.ibb.co/2ktgG8D/4.png)

![processed image and exiting program](https://i.ibb.co/4MKsyy5/5.png)

![image in default directory](https://i.ibb.co/2v836R3/6.png)

![rotated-image-90-degrees-right.bmp](https://i.ibb.co/ftw0gtM/rotated-image-90-degrees-right.png)

## License

The 24-bit Bitmap Processing Image code is open-sourced software licensed under the MIT license.