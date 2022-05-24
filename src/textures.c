/*
 * RayLib library: textures.c
 * version 3.7
 *
 * Copyright 2021 Leonardo Mendez ( mlmgerencir at gmail com )
 * Copyright 2021 Maurizio la Cecilia ( m.lacecilia at gmail com )
 * Copyright 2020 - 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbraylib.h"

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------

// Image loading functions
// NOTE: This functions do not require GPU access

// Image LoadImage(const char *fileName);                                                             // Load image from file into CPU memory (RAM)
HB_FUNC( LOADIMAGE )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      Image image = LoadImage( hb_parc( 1 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       // Load image from RAW file data
HB_FUNC( LOADIMAGERAW )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL &&
       hb_param( 4, HB_IT_INTEGER ) != NULL &&
       hb_param( 5, HB_IT_INTEGER ) != NULL )
   {
      Image image = LoadImageRaw( hb_parc( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image LoadImageAnim(const char *fileName, int *frames);                                            // Load image sequence from file (frames appended to image.data)
HB_FUNC( LOADIMAGEANIM )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      int frames;
      Image image = LoadImageAnim( hb_parc( 1 ), &frames );
      hb_storni( frames, 2 );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image LoadImageFromMemory(const char *fileType, const unsigned char *fileData, int dataSize);      // Load image from memory buffer, fileType refers to extension: i.e. "png"
HB_FUNC( LOADIMAGEFROMMEMORY )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      Image image = LoadImageFromMemory( hb_parc( 1 ), ( const unsigned char *) hb_parptr( 2 ), hb_parni( 3 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image LoadImageFromTexture(Texture2D texture); 
HB_FUNC( LOADIMAGEFROMTEXTURE )
{
     PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem, 1 );
      texture.width   = hb_arrayGetNI( pItem, 2 );
      texture.height  = hb_arrayGetNI( pItem, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem, 4 );
      texture.format  = hb_arrayGetNI( pItem, 5 );

      Image image = LoadImageFromTexture( texture );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UnloadImage(Image image);                                                                     // Unload image from CPU memory (RAM)
HB_FUNC( UNLOADIMAGE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      UnloadImage( image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool ExportImage(Image image, const char *fileName);                                               // Export image data to file, returns true on success
HB_FUNC( EXPORTIMAGE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      hb_retl( ExportImage( image, hb_parc( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool ExportImageAsCode(Image image, const char *fileName);                                         // Export image as code file defining an array of bytes, returns true on success
HB_FUNC( EXPORTIMAGEASCODE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      hb_retl( ExportImageAsCode( image, hb_parc( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image generation functions

// Image GenImageColor(int width, int height, Color color);                                           // Generate image: plain color
HB_FUNC( GENIMAGECOLOR )
{
   PHB_ITEM pItem;

   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       ( pItem = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      Image image = GenImageColor( hb_parni( 1 ), hb_parni( 2 ), color );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image GenImageGradientV(int width, int height, Color top, Color bottom);                           // Generate image: vertical gradient
HB_FUNC( GENIMAGEGRADIENTV )
{
   PHB_ITEM pItem1, pItem2;

   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       ( pItem1 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 4 &&
       ( pItem2 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Color top;

      top.r = ( unsigned char ) hb_arrayGetNI( pItem1, 1 );
      top.g = ( unsigned char ) hb_arrayGetNI( pItem1, 2 );
      top.b = ( unsigned char ) hb_arrayGetNI( pItem1, 3 );
      top.a = ( unsigned char ) hb_arrayGetNI( pItem1, 4 );

      Color bottom;

      bottom.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      bottom.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      bottom.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      bottom.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      Image image = GenImageGradientV( hb_parni( 1 ), hb_parni( 2 ), top, bottom );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image GenImageGradientH(int width, int height, Color left, Color right);                           // Generate image: horizontal gradient
HB_FUNC( GENIMAGEGRADIENTH )
{
   PHB_ITEM pItem1, pItem2;

   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       ( pItem1 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 4 &&
       ( pItem2 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Color left;

      left.r = ( unsigned char ) hb_arrayGetNI( pItem1, 1 );
      left.g = ( unsigned char ) hb_arrayGetNI( pItem1, 2 );
      left.b = ( unsigned char ) hb_arrayGetNI( pItem1, 3 );
      left.a = ( unsigned char ) hb_arrayGetNI( pItem1, 4 );

      Color right;

      right.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      right.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      right.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      right.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      Image image = GenImageGradientH( hb_parni( 1 ), hb_parni( 2 ), left, right );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);      // Generate image: radial gradient
HB_FUNC( GENIMAGEGRADIENTRADIAL )
{
   PHB_ITEM pItem1, pItem2;

   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_NUMERIC ) != NULL &&
       ( pItem1 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 4 &&
       ( pItem2 = hb_param( 5, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Color inner;

      inner.r = ( unsigned char ) hb_arrayGetNI( pItem1, 1 );
      inner.g = ( unsigned char ) hb_arrayGetNI( pItem1, 2 );
      inner.b = ( unsigned char ) hb_arrayGetNI( pItem1, 3 );
      inner.a = ( unsigned char ) hb_arrayGetNI( pItem1, 4 );

      Color outer;

      outer.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      outer.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      outer.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      outer.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      Image image = GenImageGradientRadial( hb_parni( 1 ), hb_parni( 2 ), ( float ) hb_parnd( 3 ), inner, outer );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);    // Generate image: checked
HB_FUNC( GENIMAGECHECKED )
{
   PHB_ITEM pItem1, pItem2;

   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL &&
       hb_param( 4, HB_IT_INTEGER ) != NULL &&
       ( pItem1 = hb_param( 5, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 4 &&
       ( pItem2 = hb_param( 6, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Color col1;

      col1.r = ( unsigned char ) hb_arrayGetNI( pItem1, 1 );
      col1.g = ( unsigned char ) hb_arrayGetNI( pItem1, 2 );
      col1.b = ( unsigned char ) hb_arrayGetNI( pItem1, 3 );
      col1.a = ( unsigned char ) hb_arrayGetNI( pItem1, 4 );

      Color col2;

      col2.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      col2.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      col2.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      col2.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      Image image = GenImageChecked( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), col1, col2 );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image GenImageWhiteNoise(int width, int height, float factor);                                     // Generate image: white noise
HB_FUNC( GENIMAGEWHITENOISE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
      Image image = GenImageWhiteNoise( hb_parni( 1 ), hb_parni( 2 ), ( float ) hb_parnd( 3 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image GenImageCellular(int width, int height, int tileSize);                                       // Generate image: cellular algorithm. Bigger tileSize means bigger cells
HB_FUNC( GENIMAGECELLULAR )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      Image image = GenImageCellular( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image manipulation functions

// Image ImageCopy(Image image);                                                                      // Create an image duplicate (useful for transformations)
HB_FUNC( IMAGECOPY )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      Image imageRet = ImageCopy( image );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, imageRet.data );
      hb_arraySetNI( info, 2, imageRet.width );
      hb_arraySetNI( info, 3, imageRet.height );
      hb_arraySetNI( info, 4, imageRet.mipmaps );
      hb_arraySetNI( info, 5, imageRet.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image ImageFromImage(Image image, Rectangle rec);                                                  // Create an image from another image piece
HB_FUNC( IMAGEFROMIMAGE )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Rectangle rec;

      rec.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      rec.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      rec.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      rec.height = ( float ) hb_arrayGetND( pItem2, 4 );

      Image imageRet = ImageFromImage( image, rec );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, imageRet.data );
      hb_arraySetNI( info, 2, imageRet.width );
      hb_arraySetNI( info, 3, imageRet.height );
      hb_arraySetNI( info, 4, imageRet.mipmaps );
      hb_arraySetNI( info, 5, imageRet.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image ImageText(const char *text, int fontSize, Color color);                                      // Create an image from text (default font)
HB_FUNC( IMAGETEXT )
{
     PHB_ITEM pItem;

   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       ( pItem = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      Image image = ImageText( hb_parc( 1 ), hb_parni( 2 ), color );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetPtr( info, 1, image.data );
      hb_arraySetNI( info, 2, image.width );
      hb_arraySetNI( info, 3, image.height );
      hb_arraySetNI( info, 4, image.mipmaps );
      hb_arraySetNI( info, 5, image.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);         // Create an image from text (custom sprite font)
HB_FUNC( IMAGETEXTEX )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 6 &&
                  hb_param( 2, HB_IT_STRING  ) != NULL &&
                  hb_param( 3, HB_IT_NUMERIC ) != NULL &&
                  hb_param( 4, HB_IT_NUMERIC ) != NULL &&
       ( pItem2 = hb_param( 5, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Font font;

      font.baseSize     = hb_arrayGetNI( pItem1, 1 );
      font.glyphCount   = hb_arrayGetNI( pItem1, 2 );
      font.glyphPadding = hb_arrayGetNI( pItem1, 3 );

         // Texture2D texture
         PHB_ITEM pSubarrayTexture2D = hb_arrayGetItemPtr( pItem1, 4 );

         font.texture.id      = ( unsigned int ) hb_arrayGetNI( pSubarrayTexture2D, 1 );
         font.texture.width   = hb_arrayGetNI( pSubarrayTexture2D, 2 );
         font.texture.height  = hb_arrayGetNI( pSubarrayTexture2D, 3 );
         font.texture.mipmaps = hb_arrayGetNI( pSubarrayTexture2D, 4 );
         font.texture.format  = hb_arrayGetNI( pSubarrayTexture2D, 5 );

      font.recs   = hb_arrayGetPtr( pItem2, 5 );
      font.glyphs = hb_arrayGetPtr( pItem2, 6 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      Image imageret = ImageTextEx( font, hb_parc( 2 ), ( float ) hb_parnd( 3 ), ( float ) hb_parnd( 4 ), tint );

      PHB_ITEM pImageTextExArray = hb_itemArrayNew( 5 );

      hb_arraySetPtr( pImageTextExArray, 1, imageret.data );
      hb_arraySetNI( pImageTextExArray, 2, imageret.width );
      hb_arraySetNI( pImageTextExArray, 3, imageret.height );
      hb_arraySetNI( pImageTextExArray, 4, imageret.mipmaps );
      hb_arraySetNI( pImageTextExArray, 5, imageret.format );

      hb_itemReturnRelease( pImageTextExArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageFormat(Image *image, int newFormat);                                                     // Convert image data to desired format
HB_FUNC( IMAGEFORMAT )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 &&
                 hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageFormat( &image, hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageToPOT(Image *image, Color fill);                                                         // Convert image to POT (power-of-two)
HB_FUNC( IMAGETOPOT )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Color fill;

      fill.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      fill.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      fill.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      fill.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageToPOT( &image, fill );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageCrop(Image *image, Rectangle crop);                                                      // Crop an image to a defined rectangle
HB_FUNC( IMAGECROP )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Rectangle crop;

      crop.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      crop.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      crop.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      crop.height = ( float ) hb_arrayGetND( pItem2, 4 );

      ImageCrop( &image, crop );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageAlphaCrop(Image *image, float threshold);                                                // Crop image depending on alpha value
HB_FUNC( IMAGEALPHACROP )
{
   PHB_ITEM pItem1;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      ImageAlphaCrop( &image, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageAlphaClear(Image *image, Color color, float threshold);                                  // Clear alpha channel to desired color
HB_FUNC( IMAGEALPHACLEAR )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 && hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageAlphaClear( &image, color, ( float ) hb_parnd( 3 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageAlphaMask(Image *image, Image alphaMask);                                                // Apply alpha mask to image
HB_FUNC( IMAGEALPHAMASK )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Image alphaMask;

      alphaMask.data    =  hb_arrayGetPtr( pItem2, 1 );
      alphaMask.width   =  hb_arrayGetNI( pItem2, 2 );
      alphaMask.height  =  hb_arrayGetNI( pItem2, 3 );
      alphaMask.mipmaps =  hb_arrayGetNI( pItem2, 4 );
      alphaMask.format  =  hb_arrayGetNI( pItem2, 5 );

      ImageAlphaMask( &image, alphaMask );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageAlphaPremultiply(Image *image);                                                          // Premultiply alpha channel
HB_FUNC( IMAGEALPHAPREMULTIPLY )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageAlphaPremultiply( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageResize(Image *image, int newWidth, int newHeight);                                       // Resize image (Bicubic scaling algorithm)
HB_FUNC( IMAGERESIZE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 &&
                 hb_param( 2, HB_IT_INTEGER ) != NULL &&
                 hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageResize( &image, hb_parni( 2 ), hb_parni( 3 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageResizeNN(Image *image, int newWidth,int newHeight);                                      // Resize image (Nearest-Neighbor scaling algorithm)
HB_FUNC( IMAGERESIZENN )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 &&
                 hb_param( 2, HB_IT_INTEGER ) != NULL &&
                 hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageResizeNN( &image, hb_parni( 2 ), hb_parni( 3 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);  // Resize canvas and fill with color
HB_FUNC( IMAGERESIZECANVAS )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
                  hb_param( 2, HB_IT_INTEGER ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
                  hb_param( 4, HB_IT_INTEGER ) != NULL &&
                  hb_param( 5, HB_IT_INTEGER ) != NULL &&
       ( pItem2 = hb_param( 6, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageResizeCanvas( &image, hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ), color );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageMipmaps(Image *image);                                                                   // Generate all mipmap levels for a provided image
HB_FUNC( IMAGEMIPMAPS )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageMipmaps( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
HB_FUNC( IMAGEDITHER )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 &&
                 hb_param( 2, HB_IT_INTEGER ) != NULL &&
                 hb_param( 3, HB_IT_INTEGER ) != NULL &&
                 hb_param( 4, HB_IT_INTEGER ) != NULL &&
                 hb_param( 5, HB_IT_INTEGER ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageDither( &image, hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageFlipVertical(Image *image);                                                              // Flip image vertically
HB_FUNC( IMAGEFLIPVERTICAL )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageFlipVertical( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageFlipHorizontal(Image *image);                                                            // Flip image horizontally
HB_FUNC( IMAGEFLIPHORIZONTAL )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageFlipHorizontal( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageRotateCW(Image *image);                                                                  // Rotate image clockwise 90deg
HB_FUNC( IMAGEROTATECW )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageRotateCW( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageRotateCCW(Image *image);                                                                 // Rotate image counter-clockwise 90deg
HB_FUNC( IMAGEROTATECCW )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageRotateCCW( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageColorTint(Image *image, Color color);                                                    // Modify image color: tint
HB_FUNC( IMAGECOLORTINT )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageColorTint( &image, color );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageColorInvert(Image *image);                                                               // Modify image color: invert
HB_FUNC( IMAGECOLORINVERT )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageColorInvert( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageColorGrayscale(Image *image);                                                            // Modify image color: grayscale
HB_FUNC( IMAGECOLORGRAYSCALE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageColorGrayscale( &image );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageColorContrast(Image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
HB_FUNC( IMAGECOLORCONTRAST )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageColorContrast( &image, hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageColorBrightness(Image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
HB_FUNC( IMAGECOLORBRIGHTNESS )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      ImageColorBrightness( &image, hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageColorReplace(Image *image, Color color, Color replace);                                  // Modify image color: replace color
HB_FUNC( IMAGECOLORREPLACE )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem1, 1 );
      image.width   =  hb_arrayGetNI( pItem1, 2 );
      image.height  =  hb_arrayGetNI( pItem1, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      image.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      Color replace;

      replace.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      replace.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      replace.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      replace.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      ImageColorReplace( &image, color, replace );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color *LoadImageColors(Image image);                                                               // Load color data from image as a Color array (RGBA - 32bit)
// Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorsCount);                        // Load colors palette from image as a Color array (RGBA - 32bit)

// void UnloadImageColors(Color *colors);                                                             // Unload color data loaded with LoadImageColors()
HB_FUNC( UNLOADIMAGECOLORS )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      UnloadImageColors( &color );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UnloadImagePalette(Color *colors);                                                            // Unload colors palette loaded with LoadImagePalette()
HB_FUNC( UNLOADIMAGEPALETTE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      UnloadImagePalette( &color );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Rectangle GetImageAlphaBorder(Image image, float threshold);                                       // Get image alpha border rectangle
HB_FUNC( GETIMAGEALPHABORDER )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      Rectangle rec = GetImageAlphaBorder( image, ( float ) hb_parnd( 2 ) );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetND( info, 1, ( float ) rec.x );
      hb_arraySetND( info, 2, ( float ) rec.y );
      hb_arraySetND( info, 3, ( float ) rec.width );
      hb_arraySetND( info, 4, ( float ) rec.height );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Image drawing functions
// NOTE: Image software-rendering functions (CPU)

// void ImageClearBackground(Image *dst, Color color);                                                // Clear image background with given color
HB_FUNC( ImageClearBackground )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageClearBackground( &dst, color );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawPixel(Image *dst, int posX, int posY, Color color);                                  // Draw pixel within an image
HB_FUNC( IMAGEDRAWPIXEL )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
                  hb_param( 2, HB_IT_INTEGER ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
       ( pItem2 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageDrawPixel( &dst, hb_parni( 2 ), hb_parni( 3 ), color );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawPixelV(Image *dst, Vector2 position, Color color);                                   // Draw pixel within an image (Vector version)
HB_FUNC( IMAGEDRAWPIXELV )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem2, 1 );
      position.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      ImageDrawPixelV( &dst, position, color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color); // Draw line within an image
HB_FUNC( IMAGEDRAWLINE )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
                  hb_param( 2, HB_IT_INTEGER ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
                  hb_param( 4, HB_IT_INTEGER ) != NULL &&
                  hb_param( 5, HB_IT_INTEGER ) != NULL &&
       ( pItem2 = hb_param( 6, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageDrawLine( &dst, hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ), color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);                          // Draw line within an image (Vector version)
HB_FUNC( IMAGEDRAWLINEV )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 2 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Vector2 start;

      start.x = ( float ) hb_arrayGetND( pItem2, 1 );
      start.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Vector2 end;

      end.x = ( float ) hb_arrayGetND( pItem3, 1 );
      end.y = ( float ) hb_arrayGetND( pItem3, 2 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem4, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem4, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem4, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem4, 4 );

      ImageDrawLineV( &dst, start, end, color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);               // Draw circle within an image
HB_FUNC( IMAGEDRAWCIRCLE )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
                  hb_param( 2, HB_IT_INTEGER ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
                  hb_param( 4, HB_IT_INTEGER ) != NULL &&
       ( pItem2 = hb_param( 5, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageDrawCircle( &dst, hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);                        // Draw circle within an image (Vector version)
HB_FUNC( IMAGEDRAWCIRCLEV )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
       ( pItem3 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Vector2 center;

      center.x = ( float ) hb_arrayGetND( pItem2, 1 );
      center.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      ImageDrawCircleV( &dst, center, hb_parni( 3 ), color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);       // Draw rectangle within an image
HB_FUNC( IMAGEDRAWRECTANGLE )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
                  hb_param( 2, HB_IT_INTEGER ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
                  hb_param( 4, HB_IT_INTEGER ) != NULL &&
                  hb_param( 5, HB_IT_INTEGER ) != NULL &&
       ( pItem2 = hb_param( 6, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageDrawRectangle( &dst, hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ), color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);                 // Draw rectangle within an image (Vector version)
HB_FUNC( IMAGEDRAWRECTANGLEV )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
       ( pItem3 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 2 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem2, 1 );
      position.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Vector2 size;

      size.x = ( float ) hb_arrayGetND( pItem3, 1 );
      size.y = ( float ) hb_arrayGetND( pItem3, 2 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem4, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem4, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem4, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem4, 4 );

      ImageDrawRectangleV( &dst, position, size, color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);                                // Draw rectangle within an image
HB_FUNC( IMAGEDRAWRECTANGLEREC )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Rectangle rec;

      rec.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      rec.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      rec.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      rec.height = ( float ) hb_arrayGetND( pItem2, 4 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      ImageDrawRectangleRec( &dst, rec, color );

   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawRectangleLines(Image *dst, Rectangle rec, int thick, Color color);                   // Draw rectangle lines within an image
HB_FUNC( IMAGEDRAWRECTANGLELINES )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
       ( pItem3 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Rectangle rec;

      rec.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      rec.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      rec.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      rec.height = ( float ) hb_arrayGetND( pItem2, 4 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      ImageDrawRectangleLines( &dst, rec, hb_parni( 3 ), color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);             // Draw a source image within a destination image (tint applied to source)
HB_FUNC( IMAGEDRAW )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4, pItem5;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 5 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 4 &&
       ( pItem5 = hb_param( 5, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem5 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Image src;

      src.data    =  hb_arrayGetPtr( pItem2, 1 );
      src.width   =  hb_arrayGetNI( pItem2, 2 );
      src.height  =  hb_arrayGetNI( pItem2, 3 );
      src.mipmaps =  hb_arrayGetNI( pItem2, 4 );
      src.format  =  hb_arrayGetNI( pItem2, 5 );

      Rectangle srcRec;

      srcRec.x      = ( float ) hb_arrayGetND( pItem3, 1 );
      srcRec.y      = ( float ) hb_arrayGetND( pItem3, 2 );
      srcRec.width  = ( float ) hb_arrayGetND( pItem3, 3 );
      srcRec.height = ( float ) hb_arrayGetND( pItem3, 4 );

      Rectangle dstRec;

      dstRec.x      = ( float ) hb_arrayGetND( pItem4, 1 );
      dstRec.y      = ( float ) hb_arrayGetND( pItem4, 2 );
      dstRec.width  = ( float ) hb_arrayGetND( pItem4, 3 );
      dstRec.height = ( float ) hb_arrayGetND( pItem4, 4 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem5, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem5, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem5, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem5, 4 );

      ImageDraw( &dst, src, srcRec, dstRec, tint );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);   // Draw text (using default font) within an image (destination)
HB_FUNC( IMAGEDRAWTEXT )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
                  hb_param( 2, HB_IT_STRING ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
                  hb_param( 4, HB_IT_INTEGER ) != NULL &&
                  hb_param( 5, HB_IT_INTEGER ) != NULL &&
       ( pItem2 = hb_param( 6, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      ImageDrawText( &dst, hb_parc( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ), color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text (custom sprite font) within an image (destination)
HB_FUNC( IMAGEDRAWTEXTEX )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 6 &&
                  hb_param( 3, HB_IT_STRING )  != NULL &&
       ( pItem3 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 2 &&
                  hb_param( 5, HB_IT_NUMERIC ) != NULL &&
                  hb_param( 6, HB_IT_NUMERIC ) != NULL &&
       ( pItem4 = hb_param( 7, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 4 )
   {
      Image dst;

      dst.data    =  hb_arrayGetPtr( pItem1, 1 );
      dst.width   =  hb_arrayGetNI( pItem1, 2 );
      dst.height  =  hb_arrayGetNI( pItem1, 3 );
      dst.mipmaps =  hb_arrayGetNI( pItem1, 4 );
      dst.format  =  hb_arrayGetNI( pItem1, 5 );

      Font font;

      font.baseSize     = hb_arrayGetNI( pItem2, 1 );
      font.glyphCount   = hb_arrayGetNI( pItem2, 2 );
      font.glyphPadding = hb_arrayGetNI( pItem2, 3 );

         //Texture2D texture
         PHB_ITEM pSubarrayTexture2D = hb_arrayGetItemPtr( pItem2, 4 );

         font.texture.id      = ( unsigned int ) hb_arrayGetNI( pSubarrayTexture2D, 1 );
         font.texture.width   = hb_arrayGetNI( pSubarrayTexture2D, 2 );
         font.texture.height  = hb_arrayGetNI( pSubarrayTexture2D, 3 );
         font.texture.mipmaps = hb_arrayGetNI( pSubarrayTexture2D, 4 );
         font.texture.format  = hb_arrayGetNI( pSubarrayTexture2D, 5 );

      font.recs   = hb_arrayGetPtr( pItem2, 5 );
      font.glyphs = hb_arrayGetPtr( pItem2, 6 );

      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem3, 1 );
      position.y = ( float ) hb_arrayGetND( pItem3, 2 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem4, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem4, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem4, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem4, 4 );

      ImageDrawTextEx( &dst, font, hb_parc( 3 ), position, ( float ) hb_parnd( 5 ), ( float ) hb_parnd( 6 ), tint );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Texture loading functions
// NOTE: These functions require GPU access

// Texture2D LoadTexture(const char *fileName);                                                       // Load texture from file into GPU memory (VRAM)
HB_FUNC( LOADTEXTURE )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      Texture2D texture2d = LoadTexture( hb_parc( 1 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetNI( info, 1, ( unsigned int ) texture2d.id );
      hb_arraySetNI( info, 2, texture2d.width );
      hb_arraySetNI( info, 3, texture2d.height );
      hb_arraySetNI( info, 4, texture2d.mipmaps );
      hb_arraySetNI( info, 5, texture2d.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
HB_FUNC( LOADTEXTUREFROMIMAGE )
{
    PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Image image;

      image.data    =  ( void * )hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      Texture2D texture2d = LoadTextureFromImage( image );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetNI( info, 1, ( unsigned int ) texture2d.id );
      hb_arraySetNI( info, 2, texture2d.width );
      hb_arraySetNI( info, 3, texture2d.height );
      hb_arraySetNI( info, 4, texture2d.mipmaps );
      hb_arraySetNI( info, 5, texture2d.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// TextureCubemap LoadTextureCubemap(Image image, int layoutType);                                    // Load cubemap from image, multiple image cubemap layouts supported
HB_FUNC( LOADTEXTURECUBEMAP )
{
    PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      Image image;

      image.data    =  hb_arrayGetPtr( pItem, 1 );
      image.width   =  hb_arrayGetNI( pItem, 2 );
      image.height  =  hb_arrayGetNI( pItem, 3 );
      image.mipmaps =  hb_arrayGetNI( pItem, 4 );
      image.format  =  hb_arrayGetNI( pItem, 5 );

      TextureCubemap texturecubemap = LoadTextureCubemap( image, hb_parni( 2 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetNI( info, 1, ( unsigned int ) texturecubemap.id );
      hb_arraySetNI( info, 2, texturecubemap.width );
      hb_arraySetNI( info, 3, texturecubemap.height );
      hb_arraySetNI( info, 4, texturecubemap.mipmaps );
      hb_arraySetNI( info, 5, texturecubemap.format );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load texture for rendering (framebuffer)
HB_FUNC( LOADRENDERTEXTURE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      RenderTexture2D rendertexture2d = LoadRenderTexture( hb_parni( 1 ), hb_parni( 2 ) );

      PHB_ITEM pRenderTextureArray = hb_itemArrayNew( 3 );

      hb_arraySetNI( pRenderTextureArray, 1, rendertexture2d.id );

      PHB_ITEM pSubarray = hb_arrayGetItemPtr( pRenderTextureArray, 2 );

      hb_arrayNew( pSubarray, 5 );
      hb_arraySetNI( pSubarray, 1, rendertexture2d.texture.id );
      hb_arraySetNI( pSubarray, 2, rendertexture2d.texture.width );
      hb_arraySetNI( pSubarray, 3, rendertexture2d.texture.height );
      hb_arraySetNI( pSubarray, 4, rendertexture2d.texture.mipmaps );
      hb_arraySetNI( pSubarray, 5, rendertexture2d.texture.format );

      pSubarray = hb_arrayGetItemPtr( pRenderTextureArray, 3 );
      hb_arrayNew( pSubarray, 5 );
      hb_arraySetNI( pSubarray, 1, rendertexture2d.depth.id );
      hb_arraySetNI( pSubarray, 2, rendertexture2d.depth.width );
      hb_arraySetNI( pSubarray, 3, rendertexture2d.depth.height );
      hb_arraySetNI( pSubarray, 4, rendertexture2d.depth.mipmaps );
      hb_arraySetNI( pSubarray, 5, rendertexture2d.depth.format );

      hb_itemReturnRelease( pRenderTextureArray );
      hb_itemRelease( pSubarray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UnloadTexture(Texture2D texture);                                                             // Unload texture from GPU memory (VRAM)
HB_FUNC( UNLOADTEXTURE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem, 1 );
      texture.width   = hb_arrayGetNI( pItem, 2 );
      texture.height  = hb_arrayGetNI( pItem, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem, 4 );
      texture.format  = hb_arrayGetNI( pItem, 5 );

      UnloadTexture( texture );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)

// void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
HB_FUNC( UPDATETEXTURE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_POINTER ) != NULL )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem, 1 );
      texture.width   = hb_arrayGetNI( pItem, 2 );
      texture.height  = hb_arrayGetNI( pItem, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem, 4 );
      texture.format  = hb_arrayGetNI( pItem, 5 );

      UpdateTexture( texture, hb_parptr( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data
HB_FUNC( UPDATETEXTUREREC )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
                  hb_param( 3, HB_IT_POINTER ) != NULL )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Rectangle rec;

      rec.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      rec.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      rec.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      rec.height = ( float ) hb_arrayGetND( pItem2, 4 );

      UpdateTextureRec( texture, rec, hb_parptr( 3 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
// Texture configuration functions

// void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
HB_FUNC( GENTEXTUREMIPMAPS )
{
     PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem, 1 );
      texture.width   = hb_arrayGetNI( pItem, 2 );
      texture.height  = hb_arrayGetNI( pItem, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem, 4 );
      texture.format  = hb_arrayGetNI( pItem, 5 );

      GenTextureMipmaps( &texture );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetTextureFilter(Texture2D texture, int filterMode);                                          // Set texture scaling filter mode
HB_FUNC( SETTEXTUREFILTER )
{
     PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem, 1 );
      texture.width   = hb_arrayGetNI( pItem, 2 );
      texture.height  = hb_arrayGetNI( pItem, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem, 4 );
      texture.format  = hb_arrayGetNI( pItem, 5 );

      SetTextureFilter( texture, hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetTextureWrap(Texture2D texture, int wrapMode);                                              // Set texture wrapping mode
HB_FUNC( SetTextureWrap )
{
     PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem, 1 );
      texture.width   = hb_arrayGetNI( pItem, 2 );
      texture.height  = hb_arrayGetNI( pItem, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem, 4 );
      texture.format  = hb_arrayGetNI( pItem, 5 );

      SetTextureWrap( texture, hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Texture drawing functions

// void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
HB_FUNC( DRAWTEXTURE )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
                  hb_param( 2, HB_IT_INTEGER ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
       ( pItem2 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      DrawTexture( texture, hb_parni( 2 ), hb_parni( 3 ), tint );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
HB_FUNC( DRAWTEXTUREV )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem2, 1 );
      position.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      DrawTextureV( texture, position, tint );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
HB_FUNC( DRAWTEXTUREEX )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
                  hb_param( 3, HB_IT_NUMERIC ) != NULL &&
                  hb_param( 4, HB_IT_NUMERIC ) != NULL &&
       ( pItem3 = hb_param( 5, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem2, 1 );
      position.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      DrawTextureEx( texture, position, ( float ) hb_parnd( 3 ), ( float ) hb_parnd( 4 ), tint );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);         // Draw a part of a texture defined by a rectangle
HB_FUNC( DRAWTEXTUREREC )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 2 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Rectangle source;

      source.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      source.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      source.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      source.height = ( float ) hb_arrayGetND( pItem2, 4 );

      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem3, 1 );
      position.y = ( float ) hb_arrayGetND( pItem3, 2 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem4, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem4, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem4, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem4, 4 );

      DrawTextureRec( texture, source, position, tint );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint);  // Draw texture quad with tiling and offset parameters
HB_FUNC( DRAWTEXTUREQUAD )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4, pItem5;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 2 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 4 &&
       ( pItem5 = hb_param( 5, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem5 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Vector2 tiling;

      tiling.x = ( float ) hb_arrayGetND( pItem2, 1 );
      tiling.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Vector2 offset;

      offset.x = ( float ) hb_arrayGetND( pItem3, 1 );
      offset.y = ( float ) hb_arrayGetND( pItem3, 2 );

      Rectangle quad;

      quad.x      = ( float ) hb_arrayGetND( pItem4, 1 );
      quad.y      = ( float ) hb_arrayGetND( pItem4, 2 );
      quad.width  = ( float ) hb_arrayGetND( pItem4, 3 );
      quad.height = ( float ) hb_arrayGetND( pItem4, 4 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem5, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem5, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem5, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem5, 4 );

      DrawTextureQuad( texture, tiling, offset, quad, tint );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint);  // Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
HB_FUNC( DRAWTEXTURETILED )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4, pItem5;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 2 &&
                  hb_param( 5, HB_IT_NUMERIC ) != NULL &&
                  hb_param( 6, HB_IT_NUMERIC ) != NULL &&
       ( pItem5 = hb_param( 7, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem5 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Rectangle source;

      source.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      source.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      source.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      source.height = ( float ) hb_arrayGetND( pItem2, 4 );

      Rectangle dest;

      dest.x      = ( float ) hb_arrayGetND( pItem3, 1 );
      dest.y      = ( float ) hb_arrayGetND( pItem3, 2 );
      dest.width  = ( float ) hb_arrayGetND( pItem3, 3 );
      dest.height = ( float ) hb_arrayGetND( pItem3, 4 );

      Vector2 origin;

      origin.x = ( float ) hb_arrayGetND( pItem4, 1 );
      origin.y = ( float ) hb_arrayGetND( pItem4, 2 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem5, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem5, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem5, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem5, 4 );

      DrawTextureTiled( texture, source, dest, origin, ( float ) hb_parnd( 5 ), ( float ) hb_parnd( 6 ), tint );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);       // Draw a part of a texture defined by a rectangle with 'pro' parameters
HB_FUNC( DRAWTEXTUREPRO )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4, pItem5;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 2 &&
                  hb_param( 5, HB_IT_NUMERIC ) != NULL &&
       ( pItem5 = hb_param( 6, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem5 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Rectangle source;

      source.x      = ( float ) hb_arrayGetND( pItem2, 1 );
      source.y      = ( float ) hb_arrayGetND( pItem2, 2 );
      source.width  = ( float ) hb_arrayGetND( pItem2, 3 );
      source.height = ( float ) hb_arrayGetND( pItem2, 4 );

      Rectangle dest;

      dest.x      = ( float ) hb_arrayGetND( pItem3, 1 );
      dest.y      = ( float ) hb_arrayGetND( pItem3, 2 );
      dest.width  = ( float ) hb_arrayGetND( pItem3, 3 );
      dest.height = ( float ) hb_arrayGetND( pItem3, 4 );

      Vector2 origin;

      origin.x = ( float ) hb_arrayGetND( pItem4, 1 );
      origin.y = ( float ) hb_arrayGetND( pItem4, 2 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem5, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem5, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem5, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem5, 4 );

      DrawTexturePro( texture, source, dest, origin, ( float ) hb_parnd( 5 ), tint );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

//void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint);   // Draws a texture (or part of it) that stretches or shrinks nicely

//void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointsCount, Color tint);      // Draw a textured polygon
HB_FUNC( DRAWTEXTUREPOLY )
{
   PHB_ITEM pItem1, pItem2, pItem3, pItem4, pItem5;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 5 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 2 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 2 &&
       ( pItem4 = hb_param( 4, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem4 ) == 2 &&
                  hb_param( 5, HB_IT_INTEGER ) != NULL &&
       ( pItem5 = hb_param( 6, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem5 ) == 4 )
   {
      Texture2D texture;

      texture.id      = ( unsigned int ) hb_arrayGetNI( pItem1, 1 );
      texture.width   = hb_arrayGetNI( pItem1, 2 );
      texture.height  = hb_arrayGetNI( pItem1, 3 );
      texture.mipmaps = hb_arrayGetNI( pItem1, 4 );
      texture.format  = hb_arrayGetNI( pItem1, 5 );

      Vector2 center;

      center.x = ( float ) hb_arrayGetND( pItem2, 1 );
      center.y = ( float ) hb_arrayGetND( pItem2, 2 );

      Vector2 points;

      points.x = ( float ) hb_arrayGetND( pItem3, 1 );
      points.y = ( float ) hb_arrayGetND( pItem3, 2 );

      Vector2 texcoords;

      texcoords.x = ( float ) hb_arrayGetND( pItem4, 1 );
      texcoords.y = ( float ) hb_arrayGetND( pItem4, 2 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem5, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem5, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem5, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem5, 4 );

      DrawTexturePoly( texture, center, &points, &texcoords, hb_parni( 5 ), tint );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color/pixel related functions

// Color Fade(Color color, float alpha);                                 // Returns color with alpha applied, alpha goes from 0.0f to 1.0f
HB_FUNC( FADE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      Color colorRet = Fade( color, ( float ) hb_parnd( 2 ) );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetNI( info, 1, ( unsigned char ) colorRet.r );
      hb_arraySetNI( info, 2, ( unsigned char ) colorRet.g );
      hb_arraySetNI( info, 3, ( unsigned char ) colorRet.b );
      hb_arraySetNI( info, 4, ( unsigned char ) colorRet.a );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int ColorToInt(Color color);                                          // Returns hexadecimal value for a Color
HB_FUNC( COLORTOINT )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      hb_retni( ColorToInt( color ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Vector4 ColorNormalize(Color color);                                  // Returns Color normalized as float [0..1]
HB_FUNC( COLORNORMALIZE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      Vector4 normalize = ColorNormalize( color );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetND( info, 1, ( float ) normalize.x );
      hb_arraySetND( info, 2, ( float ) normalize.y );
      hb_arraySetND( info, 3, ( float ) normalize.z );
      hb_arraySetND( info, 4, ( float ) normalize.w );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color ColorFromNormalized(Vector4 normalized);                        // Returns Color from normalized values [0..1]
HB_FUNC( COLORFROMNORMALIZED )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Vector4 normalized;

      normalized.x = ( float ) hb_arrayGetNI( pItem, 1 );
      normalized.y = ( float ) hb_arrayGetNI( pItem, 2 );
      normalized.z = ( float ) hb_arrayGetNI( pItem, 3 );
      normalized.w = ( float ) hb_arrayGetNI( pItem, 4 );

      Color color = ColorFromNormalized( normalized );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetND( info, 1, ( unsigned char ) color.r );
      hb_arraySetND( info, 2, ( unsigned char ) color.g );
      hb_arraySetND( info, 3, ( unsigned char ) color.b );
      hb_arraySetND( info, 4, ( unsigned char ) color.a );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Vector3 ColorToHSV(Color color);                                      // Returns HSV values for a Color
HB_FUNC( COLORTOHSV )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      Vector3 vector3 = ColorToHSV( color );

      PHB_ITEM info = hb_itemArrayNew( 3 );

      hb_arraySetND( info, 1, ( float ) vector3.x );
      hb_arraySetND( info, 2, ( float ) vector3.y );
      hb_arraySetND( info, 3, ( float ) vector3.z );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color ColorFromHSV(float hue, float saturation, float value);         // Returns a Color from HSV values
HB_FUNC( COLORFROMHSV )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL &&
       hb_param( 2, HB_IT_NUMERIC ) != NULL &&
       hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
      Color color = ColorFromHSV( ( float ) hb_parnd( 1 ), ( float ) hb_parnd( 2 ), ( float ) hb_parnd( 3 ) );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetNI( info, 1, ( unsigned char ) color.r );
      hb_arraySetNI( info, 2, ( unsigned char ) color.g );
      hb_arraySetNI( info, 3, ( unsigned char ) color.b );
      hb_arraySetNI( info, 4, ( unsigned char ) color.a );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color ColorAlpha(Color color, float alpha);                           // Returns color with alpha applied, alpha goes from 0.0f to 1.0f
HB_FUNC( COLORALPHA )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      Color colorRet = ColorAlpha( color, ( float ) hb_parnd( 2 ) );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetNI( info, 1, ( unsigned char ) colorRet.r );
      hb_arraySetNI( info, 2, ( unsigned char ) colorRet.g );
      hb_arraySetNI( info, 3, ( unsigned char ) colorRet.b );
      hb_arraySetNI( info, 4, ( unsigned char ) colorRet.a );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color ColorAlphaBlend(Color dst, Color src, Color tint);              // Returns src alpha-blended into dst color with tint
HB_FUNC( COLORALPHABLEND )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 4 &&
       ( pItem2 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
      Color dst;

      dst.r = ( unsigned char ) hb_arrayGetNI( pItem1, 1 );
      dst.g = ( unsigned char ) hb_arrayGetNI( pItem1, 2 );
      dst.b = ( unsigned char ) hb_arrayGetNI( pItem1, 3 );
      dst.a = ( unsigned char ) hb_arrayGetNI( pItem1, 4 );

      Color src;

      src.r = ( unsigned char ) hb_arrayGetNI( pItem2, 1 );
      src.g = ( unsigned char ) hb_arrayGetNI( pItem2, 2 );
      src.b = ( unsigned char ) hb_arrayGetNI( pItem2, 3 );
      src.a = ( unsigned char ) hb_arrayGetNI( pItem2, 4 );

      Color tint;

      tint.r = ( unsigned char ) hb_arrayGetNI( pItem3, 1 );
      tint.g = ( unsigned char ) hb_arrayGetNI( pItem3, 2 );
      tint.b = ( unsigned char ) hb_arrayGetNI( pItem3, 3 );
      tint.a = ( unsigned char ) hb_arrayGetNI( pItem3, 4 );

      Color color = ColorAlphaBlend( dst, src, tint );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetNI( info, 1, ( unsigned char ) color.r );
      hb_arraySetNI( info, 2, ( unsigned char ) color.g );
      hb_arraySetNI( info, 3, ( unsigned char ) color.b );
      hb_arraySetNI( info, 4, ( unsigned char ) color.a );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color GetColor(int hexValue);                                         // Get Color structure from hexadecimal value
HB_FUNC( GETCOLOR )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      Color color = GetColor( hb_parni( 1 ) );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetNI( info, 1, ( unsigned char ) color.r );
      hb_arraySetNI( info, 2, ( unsigned char ) color.g );
      hb_arraySetNI( info, 3, ( unsigned char ) color.b );
      hb_arraySetNI( info, 4, ( unsigned char ) color.a );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Color GetPixelColor(void *srcPtr, int format);                        // Get Color from a source pixel pointer of certain format
HB_FUNC( GETPIXELCOLOR )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      Color color = GetPixelColor( hb_parptr( 1 ), hb_parni( 2 ) );

      PHB_ITEM info = hb_itemArrayNew( 4 );

      hb_arraySetNI( info, 1, ( unsigned char ) color.r );
      hb_arraySetNI( info, 2, ( unsigned char ) color.g );
      hb_arraySetNI( info, 3, ( unsigned char ) color.b );
      hb_arraySetNI( info, 4, ( unsigned char ) color.a );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetPixelColor(void *dstPtr, Color color, int format);            // Set color formatted into destination pixel pointer
HB_FUNC( SETPIXELCOLOR )
{
   PHB_ITEM pItem;

   if( hb_param( 1, HB_IT_POINTER ) != NULL && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 &&
       hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      SetPixelColor( hb_parptr( 1 ), color, hb_parni( 3 )  );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetPixelDataSize(int width, int height, int format);              // Get pixel data size in bytes for certain format
HB_FUNC( GETPIXELDATASIZE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetPixelDataSize( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ) ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
