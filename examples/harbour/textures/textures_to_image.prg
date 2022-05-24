#include "hbraylib.ch"

#define TEXTURE2D_WIDTH    2
#define TEXTURE2D_HEIGHT   3

PROCEDURE Main()

   LOCAL nScreenWidth := 800
   LOCAL nScreenHeight := 450
   LOCAL aImage
   LOCAL aTexture

   InitWindow( nScreenWidth, nScreenHeight, "Harbour raylib [textures] example - texture to image" )

   aImage := LoadImage( "resources/raylib_logo.png" )
   aTexture := LoadTextureFromImage( aImage )
   UnloadImage( aImage )

   aImage := LoadImageFromTexture( aTexture )
   UnloadTexture( aTexture )

   aTexture := LoadTextureFromImage( aImage )
   UnloadImage( aImage )

   DO WHILE ! WindowShouldClose()

      BeginDrawing()

      ClearBackground( RAYWHITE )

      DrawTexture( aTexture, Int( nScreenWidth / 2 - aTexture[ TEXTURE2D_WIDTH ] / 2 ), Int( nScreenHeight / 2 - aTexture[ TEXTURE2D_HEIGHT ] / 2 ), WHITE )

      DrawText( "this IS a texture loaded from an image!", 300, 370, 10, GRAY )

      EndDrawing()

   ENDDO

   UnloadTexture( aTexture )

   CloseWindow()

   RETURN
