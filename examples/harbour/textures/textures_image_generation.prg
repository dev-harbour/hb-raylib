#include "hbraylib.ch"

PROCEDURE Main()

   LOCAL nScreenWidth := 800
   LOCAL nScreenHeight := 450

   LOCAL aVerticalGradient := GenImageGradientV( nScreenWidth, nScreenHeight, RED, BLUE )
   LOCAL aHorizontalGradient := GenImageGradientH( nScreenWidth, nScreenHeight, RED, BLUE )
   LOCAL aRadialGradient := GenImageGradientRadial( nScreenWidth, nScreenHeight, 0.0, WHITE, BLACK )
   LOCAL aChecked := GenImageChecked( nScreenWidth, nScreenHeight, 32, 32, RED, BLUE )
   LOCAL aWhiteNoise := GenImageWhiteNoise( nScreenWidth, nScreenHeight, 0.5 )
   LOCAL aCellular  := GenImageCellular( nScreenWidth, nScreenHeight, 32 )
   LOCAL aTextures[ 6 ]
   LOCAL nCurrentTexture := 1
   LOCAL i

   InitWindow( nScreenWidth, nScreenHeight, "Harbour raylib [Textures] example - procedural images generation" )

   aTextures[ 1 ] := LoadTextureFromImage( aVerticalGradient )
   aTextures[ 2 ] := LoadTextureFromImage( aHorizontalGradient )
   aTextures[ 3 ] := LoadTextureFromImage( aRadialGradient )
   aTextures[ 4 ] := LoadTextureFromImage( aChecked )
   aTextures[ 5 ] := LoadTextureFromImage( aWhiteNoise )
   aTextures[ 6 ] := LoadTextureFromImage( aCellular )

   UnloadImage( aVerticalGradient )
   UnloadImage( aHorizontalGradient )
   UnloadImage( aRadialGradient )
   UnloadImage( aChecked )
   UnloadImage( aWhiteNoise )
   UnloadImage( aCellular )

   SetTargetFPS( 60 )

   DO WHILE ! WindowShouldClose()

      IF IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) .OR. IsKeyPressed( KEY_RIGHT )
         iif( nCurrentTexture < Len( aTextures ), nCurrentTexture++, nCurrentTexture := 1 )
      ENDIF

      BeginDrawing()

      ClearBackground( RAYWHITE )

      DrawTexture( aTextures[ nCurrentTexture ], 0, 0, WHITE )

      DrawRectangle( 30, 400, 325, 30, Fade( SKYBLUE, 0.5 ) )
      DrawRectangleLines( 30, 400, 325, 30, Fade( WHITE, 0.5 ) )
      DrawText( "MOUSE LEFT BUTTON to CYCLE PROCEDURAL TEXTURES", 40, 410, 10, WHITE )

      DO CASE
      CASE nCurrentTexture = 1
         DrawText( "VERTICAL GRADIENT", 560, 10, 20, RAYWHITE )
      CASE nCurrentTexture = 2
         DrawText( "HORIZONTAL GRADIENT", 540, 10, 20, RAYWHITE )
      CASE nCurrentTexture = 3
         DrawText( "RADIAL GRADIENT", 580, 10, 20, LIGHTGRAY )
      CASE nCurrentTexture = 4
         DrawText( "CHECKED", 680, 10, 20, RAYWHITE )
      CASE nCurrentTexture = 5
         DrawText( "WHITE NOISE", 640, 10, 20, RED )
      CASE nCurrentTexture = 6
         DrawText( "CELLULAR", 670, 10, 20, RAYWHITE )
      ENDCASE
      EndDrawing()

   ENDDO

   FOR i := 1 TO Len( aTextures )
      UnloadTexture( aTextures[ i ] )
   NEXT

   CloseWindow()

   RETURN
