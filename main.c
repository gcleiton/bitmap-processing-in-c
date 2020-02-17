#include "include/bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <io.h>
#include <time.h>

char filename[100];
int choisenOption;

void delay(int number_of_seconds){ // https://www.geeksforgeeks.org/time-delay-c/ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds); 
} 

float convertByteToMegabyte(float byte){
    return (float) byte / pow(2, 20);
}

void showInterface(){
    int size;

    printf("\n\n\n%s            Hello, welcome!\n", YELLOW);
    printf("         / Which image do you want to process today?\n");
    printf("   |||||\n");
    printf("  ||O O|`____.\n");
    printf(" |||\\-/|| \\ __\\\n");
    printf(" |.--:--|  .   :\n");
    printf(" /( ):( |_.-~~_.\n");
    printf("(~m  : /  | oo:|\n");
    printf("~~~~~~~~~~~~~~~~~%s\n\n\n", NORMAL); 

    printf("Directory: ");

    if ( fgets(filename, sizeof(filename), stdin)){
        size = strlen(filename) - 1;

        if (filename[size] == '\n'){
            filename[size] = '\0';
        }
    }
}

void showMenu(){

    printf("\n\n\n%s            Me again here,\n", YELLOW);
    printf("         / What transformation do you want to do?\n");
    printf("   |||||\n");
    printf("  ||O O|`____.\n");
    printf(" |||\\-/|| \\ __\\\n");
    printf(" |.--:--|  .   :\n");
    printf(" /( ):( |_.-~~_.\n");
    printf("(~m  : /  | oo:|\n");
    printf("~~~~~~~~~~~~~~~~~%s\n\n\n", NORMAL);

    printf("1. Copy image\n");
    printf("2. Rotate 90 degrees right\n");
    printf("3. Rotate 90 degrees left\n");
    printf("4. Rotate 180 degrees\n");
    printf("5. Flip horizontally\n");
    printf("6. Flip vertically\n");
    printf("7. Apply grayscale\n");
    printf("0. Close program\n\n");

    printf("Option: ");

    scanf("%d", &choisenOption);
    
}

void showSuccess(){

    printf("\n\n\n%s        Congratulations, processed image.\n", YELLOW);
    printf("         / Don't forget to check the images directory.\n");
    printf("   |||||\n");
    printf("  ||O O|`____.\n");
    printf(" |||\\-/|| \\ __\\\n");
    printf(" |.--:--|  .   :\n");
    printf(" /( ):( |_.-~~_.\n");
    printf("(~m  : /  | oo:|\n");
    printf("~~~~~~~~~~~~~~~~~%s\n\n\n", NORMAL);
    
}

void showProgressArt(){
    printf("\n\n\n%s         / Please, wait a little bit.\n", YELLOW);
    printf("   |||||\n");
    printf("  ||O O|`____.\n");
    printf(" |||\\-/|| \\ __\\\n");
    printf(" |.--:--|  .   :\n");
    printf(" /( ):( |_.-~~_.\n");
    printf("(~m  : /  | oo:|\n");
    printf("~~~~~~~~~~~~~~~~~%s\n\n\n", NORMAL);
}

void showProgressBar(){
    int i, prefixLength, suffixLength; 
    char *progress;
	const char prefix[] = "Progress: ";
	const char suffix[] = "]";

	prefixLength = sizeof(prefix) - 1;
	suffixLength = sizeof(suffix) - 1;

	progress = calloc(100 + prefixLength + suffixLength + 1, 1);

	for (i = 0; i <= 100; i+=20){
        system("cls");
        showProgressArt();
        if(i == 100){
            system("cls");
        }
        printf("%s %d%%: [", prefix, i);
        for(int j = 0; j < 100; j++){
            progress[j] = j < i ? '|' : ' ';  
        }	
        
        printf("%s%s\n", progress, suffix);
        delay(1);
        
	}
}

void closeProgram(){
    int i;

    printf("Exiting program, wait a moment");
    for(i = 0; i < 3; i++){
        delay(1);
        printf(".");
    }

    delay(1);
    exit(1);
}

int main(){

    system("COLOR 0");
    system("cls");
    
    FILE *file, *processedFile;
    IMAGE image, processedImage;
    int i, width, height, size, dirCheck;

    showInterface();

    file = fopen(filename, "rb");

    if(file == NULL){
        printf("| WARNING | Error opening the file.\n");
    } else {
        printf("| WARNING | Image successfully opened.\n");
    }

    dirCheck = mkdir(DEFAULT_PATH);
    if(!dirCheck){
        printf("| WARNING | Created the images directory.\n");
    } else {
        printf("| WARNING | Unable to create or already exists the images directory to store the processed images.\n");
    }

    image = readImage(file);

    width = image.infoHeader.biWidth;
    height = image.infoHeader.biHeight;
    size = image.infoHeader.biSizeImage;

    printf("\nImage Information:\n\n");
    printf("Type: Bitmap 24-bit\n");
    printf("Width: %d pixels\n", width);
    printf("Height: %d pixels\n", height);
    printf("Size: %.2f megabytes\n\n", convertByteToMegabyte(size));

    printf("Please, wait a litle bit");
    for(i = 0; i < 5; i++){
        delay(1);
        printf(".");
    }
    system("cls");
    showMenu();

    system("cls");
    switch(choisenOption){
        
        case 0: closeProgram();
            break;

        case 1: 
            showProgressBar();
            processedFile = fopen(DEFAULT_PATH "copied-image.bmp", "wb");
            processedImage = copy(image);
            writeToFile(processedFile, processedImage);
            showSuccess(file, image);
            fclose(processedFile);
            closeProgram();
            break;

        case 2:
            showProgressBar();
            processedFile = fopen(DEFAULT_PATH "rotated-image-90-degrees-right.bmp", "wb");
            processedImage = rotate90DegreesRight(image);
            writeToFile(processedFile, processedImage);
            showSuccess(file, image);
            fclose(processedFile);
            closeProgram();
            break;

        case 3:
            showProgressBar();
            processedFile = fopen(DEFAULT_PATH "rotated-image-90-degrees-left.bmp", "wb");
            processedImage = rotate90DegreesLeft(image);
            writeToFile(processedFile, processedImage);
            showSuccess(file, image);
            fclose(processedFile);
            closeProgram();
            break;

        case 4:
            showProgressBar();
            processedFile = fopen(DEFAULT_PATH "rotated-image-180-degrees.bmp", "wb");
            processedImage = rotate180Degrees(image);
            writeToFile(processedFile, processedImage);
            showSuccess(file, image);
            fclose(processedFile);
            closeProgram();
            break;

        case 5:
            showProgressBar();
            processedFile = fopen(DEFAULT_PATH "flipped-image-horizontally.bmp", "wb");
            processedImage = flipHorizontally(image);
            writeToFile(processedFile, processedImage);
            showSuccess(file, image);
            fclose(processedFile);
            closeProgram();
            break;

        case 6:
            showProgressBar();
            processedFile = fopen(DEFAULT_PATH "flipped-image-vertically.bmp", "wb");
            processedImage = flipVertically(image);
            writeToFile(processedFile, processedImage);
            showSuccess(file, image);
            fclose(processedFile);
            closeProgram();
            break;

        case 7:
            showProgressBar();
            processedFile = fopen(DEFAULT_PATH "grayscaled-image.bmp", "wb");
            processedImage = applyGrayscale(image);
            writeToFile(processedFile, processedImage);
            showSuccess(file, image);
            fclose(processedFile);
            closeProgram();
            break;

    }
    
    fclose(file);

    return 0;
}