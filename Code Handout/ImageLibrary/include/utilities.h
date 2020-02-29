#include <RasterImage.h>

/** returns a RasterImage object with all color channels changed to gray. 
 *  @param img   the original RasterImage object that operations will be performed on.
 */
RasterImage gray(RasterImage img);

/** returns a RasterImage object that is a cropped version of the original image that is passed.
 *  @param img   the original RasterImage object that operations will be performed on.
 *  @param x1    the top-left corner x-coordinate of the desired crop rectangle.
 *  @param y1    the top-left corner y-coordinate of the desired crop rectangle
 *  @param x2    the bottom-right corner x-coordinate of the desired crop rectangle.
 *  @param y2    the bottom-right corner y-coordinate of the desired crop rectangle.
 */
RasterImage crop(RasterImage img, int x1, int y1, int x2, int y2);

/** returns a RasterImage object that is a horizontally mirrored version of the original image that is passed.
 *  @param img   the original RasterImage object that operations will be performed on
 */
RasterImage mirrorH(RasterImage img);

/** returns a RasterImage object that is a vertically mirrored version of the original image that is passed.
 *  @param img   the original RasterImage object that operations will be performed on
 */
RasterImage mirrorV(RasterImage img);

/** exits with 0 code if the two images provided have equal rasters, otherwise exits with 1 code.
 *  @param imgOne   the first image to be compared to the second image.
 *  @param imgTwo   the second image to be compared to the first image.
 */
void comp(RasterImage imgOne, RasterImage imgTwo);

/** returns a new output path with a .tga extension, built on a specified output directory provided by the user.
 *  @param path         this is the path of the input image, such as ../../Images/clown.tga
 *  @param outputDir    this is the path of the output directory, provided by the user. Could be something like ../output
 *  @param type         this is the type of operation that is going to be performed on the image. So, if we want to perform
 *         an operation such as mirrorV on the clown.tga file, we will pass "mirrorV" as an argument here. This is used for
 *         adding to the output string, so we can easily make clown [mirrorV].tga just by passing this argument, and won't have
 *         to have this function in each specific program, but instead can just have this one function and specify a type. 
 */
char* makeNewPath(char* path, char* outputDir, char* type);



