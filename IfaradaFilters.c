/**
* (Applie BlurFilter and Swiss Cheese Filter)
*
* Completion time: (estimation of hours spent on this program)
*
* @author (Lorenzo Ifarada), (Acuna)
* @version (a version number or a date)
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>
//TODO: finish me


#include "BmpProcessor.h"


////////////////////////////////////////////////////////////////////////////////
//MACRO DEFINITIONS

//problem assumptions
#define BMP_HEADER_SIZE 14
#define BMP_DIB_HEADER_SIZE 40
#define MAXIMUM_IMAGE_SIZE 4096
int THREAD_COUNT;
#define BitsPerPixel 3
#define RowSize(width) ((ceil(width*BitsPerPixel)/32)*4)



//TODO: finish me


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

//TODO: finish me
// Understand that there are two headers.
// You need to Read the Headers first.
// After you read the headers you can read the Pixels
// The Pixel Array will be in pArr*
struct Pixel GlobalPixel;


////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE
//TODO: finish me

// NEED TO FINISH FILTER FLAG

struct BlurFlag
        {
             struct  Pixel** PixArrFlag;
                int Flag;
        };

// Figure out how to pass the PixArrFlag to map to the PArr
void* BoxBluerFilterFlag(void* PArr,void* RowPixelSize, void* ColPixelSize) {
    {
        //RowSize & ColSize are in Pixels ;HELLO!
        //cast your passed data
        //cast my if Pixel after I check for Null capacity??? Hmmm need to research this - Action Item to DO!!!
        struct Pixel **ImageNull = NULL;
        struct Pixel **Image = (struct Pixel **) PArr;
        struct BlurFlag **PixArrFlag =(struct BlurFlag**) PArr ;

        int NeighborQuantity = 0;
        int RowSize = (int) (RowPixelSize);
        int ColSize = (int) (ColPixelSize);
        //   int RowBeginPos;
        //   int ColBeginPos;

        for (int x = 0; x < RowSize; x++) {
            for (int y = 0; y < ColSize; y++) {

                NeighborQuantity += 1;
                PixArrFlag[x][y].Flag =1;
                if (((0 <= (x - 1) && (x - 1) <= RowSize)) && (0 <= (y) && (y) <= ColSize)) {

                    PixArrFlag[x-1][y].Flag =1;
                }//Neighbor 1
                if ((0 <= (x + 1) && (x + 1) <= RowSize) && (0 <= (y) && (y) <= ColSize)) {

                    PixArrFlag[x+1][y].Flag =1;
                }//Neighbor 2
                if ((0 <= (x) && (x) <= RowSize) && (0 <= (y - 1) && (y - 1) <= ColSize)) {

                    PixArrFlag[x][y+1].Flag =1;
                }//Neighbor 3
                if ((0 <= (x) && (x) <= RowSize) && (0 <= (y + 1) && (y + 1) <= ColSize)) {

                    PixArrFlag[x-1][y].Flag = 1;
                }//Neighbor 4
                if ((0 <= (x + 1) && (x + 1) <= RowSize) && (0 <= (y + 1) && (y + 1) <= ColSize)) {

                    PixArrFlag[x-1][y].Flag = 1;
                }//Neighbor 5
                if ((0 <= (x - 1) && (x - 1) <= RowSize) && (0 <= (y - 1) && (y - 1) <= ColSize)) {

                    PixArrFlag[x-1][y].Flag = 1;
                }//Neighbor 6
                if ((0 <= (x - 1) && (x - 1) <= RowSize) && (0 <= (y + 1) && (y + 1) <= ColSize)) {

                    PixArrFlag[x-1][y].Flag = 1;
                }//Neighbor 7
                if ((0 <= (x + 1) && (x + 1) <= RowSize) && (0 <= (y - 1) && (y - 1) <= ColSize)) {

                    PixArrFlag[x-1][y].Flag = 1;
                }//Neighbor 8




            }


        }
    }
}

void* BoxBlurFilter (void* PArr,void* RowPixelSize, void* ColPixelSize)
{
    //RowSize & ColSize are in Pixels ;HELLO!
    //cast your passed data
    //cast my if Pixel after I check for Null capacity??? Hmmm need to research this - Action Item to DO!!!
    struct Pixel**  ImageNull = NULL;
    struct Pixel**  Image =(struct Pixel**) PArr;
    int NeighborQuantity = 0;
    int RowSize =(int)(RowPixelSize);
    int ColSize =(int)(ColPixelSize);
 //   int RowBeginPos;
 //   int ColBeginPos;

for(int x = 0; x < RowSize; x++) {
    for (int y = 0; y < ColSize; y++)
    {
       GlobalPixel.red +=Image[x][y].red;
       GlobalPixel.blue +=Image[x][y].blue;
       GlobalPixel.green +=Image[x][y].green;
       NeighborQuantity += 1;
       if( ((0<= (x-1) && (x-1) <=RowSize))  && (0  <= (y) && (y)<= ColSize))
        {   GlobalPixel.red=Image[x-1][y].red;
            GlobalPixel.blue=Image[x-1][y].blue;
            GlobalPixel.green=Image[x-1][y].green;
            NeighborQuantity += 1; }//Neighbor 1
       if( ( 0<= (x+1) && (x+1) <=RowSize)  && (0  <= (y) && (y) <= ColSize) )
       {
           GlobalPixel.red=Image[x+1][y].red;
           GlobalPixel.blue=Image[x+1][y].blue;
           GlobalPixel.green=Image[x+1][y].green;
           NeighborQuantity += 1;
       }//Neighbor 2
       if(( 0<= (x) && (x) <=RowSize)  && (0  <= (y-1)  && (y-1) <= ColSize)  ) {
           GlobalPixel.red = Image[x][y-1] .red;
           GlobalPixel.blue = Image[x][y-1] .blue;
           GlobalPixel.green = Image[x][y-1] .green;
           NeighborQuantity += 1;
       }//Neighbor 3
       if( (0<= (x) && (x) <=RowSize)  && (0  <= (y+1) && (y+1) <= ColSize)  )
       {
           GlobalPixel.red +=Image[x][y+1].red;
           GlobalPixel.blue +=Image[x][y+1].blue;
           GlobalPixel.green +=Image[x][y+1].green;
           NeighborQuantity += 1;
       }//Neighbor 4
       if( (0<= (x+1)  && (x+1) <=RowSize)  && (0  <= (y+1) && (y+1) <= ColSize)   )
       {
           GlobalPixel.red +=Image[x+1][y+1].red;
           GlobalPixel.blue += Image[x+1][y+1].blue;
           GlobalPixel.green +=Image[x+1][y+1].green;
           NeighborQuantity += 1;
       }//Neighbor 5
       if( (0<= (x-1) && (x-1) <=RowSize)  && (0  <= (y-1) && (y-1) <= ColSize)   )
       {
           GlobalPixel.red +=Image[x-1][y-1].red;
           GlobalPixel.blue +=Image[x-1][y-1].blue;
           GlobalPixel.green +=Image[x-1][y-1].green;
           NeighborQuantity += 1;
       }//Neighbor 6
       if( (0<= (x-1) && (x-1) <=RowSize)  && (0  <= (y+1) && (y+1) <= ColSize)    )
       {
           GlobalPixel.red +=Image[x-1][y+1].red;
           GlobalPixel.blue +=Image[x-1][y+1].blue;
           GlobalPixel.green +=Image[x-1][y+1].green;
           NeighborQuantity += 1;
       }//Neighbor 7
       if( (0<= (x+1) && (x+1) <=RowSize)  && (0  <= (y-1) && (y-1) <= ColSize)  )
       {
           GlobalPixel.red +=Image[x+1][y-1].red;
           GlobalPixel.blue +=Image[x+1][y-1].blue;
           GlobalPixel.green +=Image[x+1][y-1].green;
           NeighborQuantity += 1;
       }//Neighbor 8

       // Applying Amount of existing Neighboring Pixels(Including said Pixel)
       GlobalPixel.red     =  GlobalPixel.red / NeighborQuantity ;
       GlobalPixel.blue    =  GlobalPixel.blue / NeighborQuantity ;
       GlobalPixel.green   =  GlobalPixel.green / NeighborQuantity ;

       Image[y][x].red   = GlobalPixel.red;
       Image[y][x].blue  = GlobalPixel.blue;
       Image[y][x].green = GlobalPixel.green;
    }


    pthread_exit(GlobalPixel);
}

}
// ------------- END OF BLUR FILTER ---------------------------------------------------

struct circle
{
    int radius;
    int x;
    int y;

};

void SwissCheeseMaskFlag(void* PArr,void* width, void* height, void* randomNumber)

{
     //Intitialize  Variables
    struct Pixel **Image = (struct Pixel **) PArr;
    int NumHolesQuantity;
    int Width = (int) (width);
    int Height = (int) (height);
    int Counter;
    int AverageRadius;
    int SmallRadius;
    int LargeRadius;
    int radius;
    //Choosing Radius from Smallest Dimension
    int DimensionChoice;
    if (Width > Height) {
        DimensionChoice = Height;
    }
    else {
        DimensionChoice = Width;
    }

    // Define Number of Holes
    NumHolesQuantity = floor(.08*DimensionChoice);

    //Define Radius Sizes
    SmallRadius =  floor(.04*DimensionChoice);
    AverageRadius = floor(.08*DimensionChoice);
    LargeRadius =  floor(.16*DimensionChoice);


    int randomNumber =(int) rand() % 10;


    if(randomNumber < 2)
    {

        {
            radius = .04*SmallRadius;
            NumHolesQuantity=.08*DimensionChoice;
        };
    }
    else if( randomNumber> 2 && randomNumber <8)
    {

        {
            radius = .08*DimensionChoice;
            NumHolesQuantity=.08*DimensionChoice;
        };
    }

    else {

        {
            radius = .16 * DimensionChoice;
            NumHolesQuantity = .08 * DimensionChoice;
        };
    }






    // Coordinate Point Struct for Circle of Hole with a Flag for Masking prior to Threading.
    struct Value
    {
        int* x;
        int* y;
        struct FlagPt;
        int Flag;
    };

    struct FlagPt
    {
        int* x;
        int* y;
    };

    //Init Circle Center List Size
    struct Value CircleCenterPotentialPoints[1000];
    struct Value CircleCenterActualPoints[NumHolesQuantity];
    // Generating points for Circle List and Storing ... need to make nonrepeating values ? Hmm...
    for(int x=0 ; x < 1000 ; x++) {

        CircleCenterPotentialPoints->x[x] = (rand()) ;
        CircleCenterPotentialPoints->y[x] = (rand()) ;
    }

    //Define Uniformity Distance between Centerpoints of Holes
    int distanceBetweenHolesX =  Width/NumHolesQuantity ;
    int distanceBetweenHolesY =  Height/NumHolesQuantity;
    int FlagDistanceX = sqrt( ((distanceBetweenHolesX)*(distanceBetweenHolesX)));
    int FlagDistanceY = sqrt( (distanceBetweenHolesY)*(distanceBetweenHolesY));

    //Reading Points that fall on X-Axis and Y-Axis with Respect to Minimum Dimension Value that sets the Max # of holes.
    while(!(Counter == NumHolesQuantity)  )
    {
        int w=0;
        int t=0;

            if ((CircleCenterPotentialPoints->x[t] = Height/2) && (CircleCenterPotentialPoints->y[t] > Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceY ==0) )
            {
                CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                        Counter++;
                        t++;
                        w++;
            }
            else if ((CircleCenterPotentialPoints->x[t] > Height/2) && (CircleCenterPotentialPoints->y[t] = Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceX ==0))
            {
                CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                        Counter++;
                        t++;
                        w++;

            }
            else if ((CircleCenterPotentialPoints->x[t] = Height/2) && (CircleCenterPotentialPoints->y[t] < Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceY ==0) )
             {
                  CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                  CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                      Counter++;
                      t++;
                      w++;
              }
              else if ((CircleCenterPotentialPoints->x[t] < Height/2) && (CircleCenterPotentialPoints->y[t] = Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceX ==0))
             {
                 CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                 CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                      Counter++;
                      t++;
                      w++;


            }
            else if ( ((CircleCenterPotentialPoints->x[t] = Width/2) && (CircleCenterPotentialPoints->y[t] = Height/2)) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceX == 0) )
            {
                    CircleCenterActualPoints->x[w] = Width/2;
                    CircleCenterActualPoints->y[w] = Height/2;
                    Counter++;
                    w++;
                    t++;

            }
            else
            {
                 t++;
            }


    }
    int DistanceFromCenter;

   void generateCircleFlag(struct Value CircleCenterActualPoints, void radius )

    {
       int XRnge;
       int YRnge;
       int DistTtl =;
       int DistX;
       int DistY;
       int Ttl;
       for(int num=0 ; num < NumHolesQuantity, num++)
       {
         int Xpt = CircleCenterActualPoints->x[num];
         int Ypt=  CircleCenterActualPoints->y[num];
         for(XRnge = 0; XRnge < Width, XRnge++)
         for(YRnge = 0; YRnge < height, Y++)
         {
             DistX = ((XRnge - Xpt) * (XRnge - Xpt));
             DistY = ((YRnge - Ypt) * (YRnge- Ypt)));
             TTl = sqrt(DistX+DistY)
                     if(Ttl < radius)
                     {


                     CircleCenterActualPoints->Flag[num] = 1;


                     }
         }
       }
    }









    }








void* SwissCheeseFilter(void* PArr,void* width , void* height) {
    //Intitialize  Variables
    struct Pixel **Image = (struct Pixel **) PArr;
    int NumHolesQuantity;
    int Width = (int) (width);
    int Height = (int) (height);
    int Counter;
    int AverageRadius;
    int SmallRadius;
    int LargeRadius;
    int radius;
    //Choosing Radius from Smallest Dimension
    int DimensionChoice;
    if (Width > Height) {
        DimensionChoice = Height;
    }
    else {
        DimensionChoice = Width;
    }

    // Define Number of Holes
    NumHolesQuantity = floor(.08*DimensionChoice);

    //Define Radius Sizes
    SmallRadius =  floor(.04*DimensionChoice);
    AverageRadius = floor(.08*DimensionChoice);
    LargeRadius =  floor(.16*DimensionChoice);


    int randomNumber = rand();


    if(randomNumber < 2)
    {


            radius = .04*DimensionChoice;
            NumHolesQuantity=.08*DimensionChoice;

    }
    else if( randomNumber> 2 && randomNumber <8) {


            radius = .08*DimensionChoice;
            NumHolesQuantity=.08*DimensionChoice;

    }
    else {


            radius = .16 * DimensionChoice;
            NumHolesQuantity = .08 * DimensionChoice;

    }


// Tint the Image
 for(int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            colorShiftPixels(Image,Width,Height, 50 ,50, -50);
        }
        }



    // Coordinate Point Struct for Circle of Hole with a Flag for Masking prior to Threading.
    struct Value
    {
        int* x;
        int* y;
        struct FlagPt;
        int Flag;
    };
    struct FlagPt
    {
        int* x;
        int* y;
    };
    //Init Circle Center List Size
    struct Value CircleCenterPotentialPoints[1000];
    struct Value CircleCenterActualPoints[NumHolesQuantity];
    // Generating points for Circle List and Storing ... need to make nonrepeating values ? Hmm...
    for(int x=0 ; x < 1000 ; x++) {

        CircleCenterPotentialPoints->x[x] = (rand()) ;
        CircleCenterPotentialPoints->y[x] = (rand()) ;
    }

    //Define Uniformity Distance between Centerpoints of Holes
    int distanceBetweenHolesX =  Width/NumHolesQuantity ;
    int distanceBetweenHolesY =  Height/NumHolesQuantity;
    int FlagDistanceX = sqrt( ((distanceBetweenHolesX)*(distanceBetweenHolesX)));
    int FlagDistanceY = sqrt( (distanceBetweenHolesY)*(distanceBetweenHolesY));

    //Reading Points that fall on X-Axis and Y-Axis with Respect to Minimum Dimension Value that sets the Max # of holes.
    while(!(Counter == NumHolesQuantity)  )
    {
        int w=0;
        int t=0;

            if ((CircleCenterPotentialPoints->x[t] = Height/2) && (CircleCenterPotentialPoints->y[t] > Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceY ==0) )
            {
                CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                        Counter++;
                        t++;
                        w++;
            }
            else if ((CircleCenterPotentialPoints->x[t] > Height/2) && (CircleCenterPotentialPoints->y[t] = Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceX ==0))
            {
                CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                        Counter++;
                        t++;
                        w++;

            }
            else if ((CircleCenterPotentialPoints->x[t] = Height/2) && (CircleCenterPotentialPoints->y[t] < Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceY ==0) )
             {
                  CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                  CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                      Counter++;
                      t++;
                      w++;
              }
              else if ((CircleCenterPotentialPoints->x[t] < Height/2) && (CircleCenterPotentialPoints->y[t] = Width/2) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceX ==0))
             {
                 CircleCenterActualPoints->x[w] = CircleCenterPotentialPoints->x[t];
                 CircleCenterActualPoints->y[w] = CircleCenterPotentialPoints->y[t];
                      Counter++;
                      t++;
                      w++;


            }
            else if ( ((CircleCenterPotentialPoints->x[t] = Width/2) && (CircleCenterPotentialPoints->y[t] = Height/2)) && ((CircleCenterPotentialPoints->y[t]) % FlagDistanceX == 0) )
            {
                    CircleCenterActualPoints->x[w] = Width/2;
                    CircleCenterActualPoints->y[w] = Height/2;
                    Counter++;
                    w++;
                    t++;

            }
            else
            {
                 t++;
            }


    }











    }


// Yellow Tint


    pthread_exit(0);












}

void generateCircle(struct Value CircleCenterActualPoints, void radius )

    {
       int XRnge;
       int YRnge;
       int DistTtl ;
       int DistX;
       int DistY;
       int Ttl;
       for(int num=0 ; num < NumHolesQuantity, num++)
       {
         int Xpt = CircleCenterActualPoints->x[num];
         int Ypt=  CircleCenterActualPoints->y[num];
         for(XRnge = 0; XRnge < Width, XRnge++)
         for(YRnge = 0; YRnge < height, Y++)
         {
             DistX = ((XRnge - Xpt) * (XRnge - Xpt));
             DistY = ((YRnge - Ypt) * (YRnge- Ypt)));
             TTl = sqrt(DistX+DistY)
                     if(Ttl < radius && Flag)
                     {

                         Image[YRNGE][XRNGE]->red = 0;
                         Image[YRNGE][XRNGE]->green = 0;
                         Image[YRNGE][XRNGE]->blue =0;



                     }
         }
       }
    }






//------------ end of SWISS CHESS FILTER-------------------------------------------------



//CREATE STRUCT FOR Info of thread_info  // Use for Blur needed  // for Cheese IDK

struct thread_info{
int start;
int end;
struct Pixel** Image;
struct Pixel** ImageResult;

};


struct Flagging
{
    struct Pixel** PixelFlagged;

};

//FILE READ
void read()
{

}


//FILE WRITE
void write()
{

    //TODO: finish me

}


// Compute BoxBlurFilter Threading
void BoxBlurThreading()
{
     /// Threads for BoxBlur

    // TotalRowSize in Pixels Recorded for BoxBlurFilter(with Padding)
    int TotalRowSize = RowSize(width);

    // PixelCountWidth Per Thread(With Padding)
    int PixelCountWidthPerThread = TotalRowSize/THREAD_COUNT;

    //ReadToEachThreadPixel
    // Loop for Each Potential
    // Read the Data into each Block
    struct thread_info*  Thread_Info[THREAD_COUNT];
    int a,b;
    for(int x=1; x <= THREAD_COUNT ;x++)
    {
         for(int j=0 ; j < height;j++)
         {
             for (int y = 0; y < PixelCountWidthPerThread; y++)
             {
                 //CREATE THREAD MEMORY FOR PIXEL MEMORY INTO INDIVIDUAL THREADS with xtra space so I can pass "access" of other pixels into Threads
                 if(Thread_Info[1]->Image[0][0]  )
                 {
                     Thread_Info[1]->Image = (struct Pixel **) malloc((sizeof(struct Pixel *)) * (1 / THREAD_COUNT)+((sizeof(struct Pixel*))/TotalRowSize));
                 }                                                        //sizeof(Pixel*)*height*TotalRowSize =
                 else if(Thread_Info[1]->Image[0][THREAD_COUNT])
                 {

                 }
                 else {
                     Thread_Info->Thread[THREAD_COUNT] = (struct Pixel **) malloc(
                             ((sizeof(struct Pixel **)) * (1 / THREAD_COUNT))+((sizeof(struct Pixel**))/TotalRowSize)*2);
                 }

                 // PASS THE DATA TO THE THREADS AFTER
                 if(Thread_Info->ImageResult[1] || Thread_Info->ImageResult[THREAD_COUNT] )
                 {
                     Thread_Info->ImageResult[1] = (struct Pixel **) malloc((sizeof(struct Pixel **)) * (1 / THREAD_COUNT)+((sizeof(struct Pixel**))/TotalRowSize));
                 }
                 else {
                     Thread_Info->ImageResult[THREAD_COUNT] = (struct Pixel **) malloc(
                             ((sizeof(struct Pixel **)) * (1 / THREAD_COUNT))+((sizeof(struct Pixel**))/TotalRowSize)*2);
                 }
                 for (int z = 0; z < height; z++)
                 {
                     Thread_Info[THREAD_COUNT]->Image[y][z] = pArr[a][b];
                     a++;
                     b++;
                 }
             }
         }
    }


       //Threads for BoxBlur;

    //pthread_create for THREAD_AMOUNT OF THREADS

    for(int i = 0 ; i < THREAD_COUNT; i++)
    {
        pthread_create(&tid[i],NULL , BoxBlurFilter(pArr,TotalRowSize, height),  &Thread_Info[i]  );
    }

    //pthread_join for THREAD_AMOUNT OF THREADS
    for(int i = 0 ; i < THREAD_COUNT; i++)
    {
        pthread_join(&tid[i],NULL , BoxBlurFilter(PixelImageDivided_dyn), Thread_Info->ImageResult[i][i]  );
    }


}

// Compute SwissCheeseFilterThreading
void SwissCheeseFilterThread()
{



     //Threads for SwissCheeseFilter;

    //pthread_create for THREAD_AMOUNT OF THREADS

    for(int i = 0 ; i < THREAD_COUNT; i++)
    {
        pthread_create(&tid[i],NULL , SwissCheeseFilter(&pArr,&Thread_Info->Image, height),  &  );
    }

    //pthread_join for THREAD_AMOUNT OF THREADS
    for(int i = 0 ; i < THREAD_COUNT; i++)
    {
        pthread_join(tid[i],NULL , SwissCheeseFilter(PixelImageDivided_dyn), &Thread_Info->ImageResult[i]  );
    }


}

void copyfile(FILE *in, FILE *out)
{
  int ch;

  while ((ch = fgetc(in)) != EOF) {
    fputc(ch, out);
  }
}

void main(int argc, char* argv[]) {
    //Create how many threads you want
    printf("Hello User Enter your THREAD_COUNT");
    scanf("%s\n",&THREAD_COUNT);
    pthread_t tid[THREAD_COUNT];

 int i;
  FILE *fileptr;


    //Extract Data such as width,Pixel Info,
    //Creating option selection for Linux
    int option;
    // put ':' at the starting of the string so compiler can distinguish between '?' and ':'
    while((option = getopt(argc, argv, ":bcriwo")) != -1)
    { //get option from the getopt() method
        switch(option){
            //For option i, r, l, print that these are options
            case 'b':
                //blur filter call here
                BoxBlurThreading();
            case 'c':
                // cheese filter call here
                SwissCheeseFilterThread();
            case 'r':
                printf("Given Option: %c\n", option);
                break;
            case 'i': for (i = 1; i < argc; i++) {
    fileptr = fopen(argv[i], "rb");

     //Read BMP HEADER
    struct BMP_Header* BMPHeader = (struct BMP_Header*) malloc(sizeof(BMPHeader));
     readBMPHeader(fileptr,   BMPHeader);

    //READ DIB HEADER
    struct DIB_Header* DIBHeader= (struct DIB_Header*)malloc(sizeof(BMPHeader));
     readDIBHeader(fileptr,  DIBHeader);

     //READ PIXEL FILE      and width and Height without padding                   // Make need to revisit for Dynamic Memory Location of Each Thread and Data Split
     struct Pixel** pArr = (struct Pixel** )malloc(sizeof(pArr));
     int width;
     int height;
     readPixelsBMP(fileptr ,pArr,  width,  height);



    

            break;
            case 'o':
                //Write to a file!

    //Write BMP HEADER TO FILE
    writeBMPHeader(fileptr,   BMPHeader);

    //Write DIB HEADER TO FILE
    writeDIBHeader(fileptr,  DIBHeader);

    //Write IMAGE TO FILE
    writePixelsBMP(fileptr, pArr,  width,  height);

     if (fileptr != NULL) {
      copyfile(fileptr, stdout);
      fclose(fileptr);
}
                break;
            case '?': //used for some unknown options
                printf("unknown option: %c\n", optopt);
                break;
        }
    }
    for(; optind < argc; optind++){ //when some extra arguments are passed
        printf("Given extra arguments: %s\n", argv[optind]);


    return;
}
    }
    }