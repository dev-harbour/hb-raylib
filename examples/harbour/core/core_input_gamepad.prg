#include "hbraylib.ch"

#define XBOX360_LEGACY_NAME_ID "Xbox Controller"

#ifdef  PLATFORM_RPI
#define XBOX360_NAME_ID        "Microsoft X-Box 360 pad"
#define PS3_NAME_ID            "PLAYSTATION(R)3 Controller"
#else
#define XBOX360_NAME_ID        "Xbox 360 Controller"
#define PS3_NAME_ID            "PLAYSTATION(R)3 Controller"
#endif

PROCEDURE Main()

   LOCAL nScreenWidth := 800
   LOCAL nScreenHeight := 450
   LOCAL aTexPs3Pad
   LOCAL aTexXboxPad
   LOCAL i

   InitWindow( nScreenWidth, nScreenHeight, "Harbour and raylib [core] example - gamepad input" )

   aTexPs3Pad  := LoadTexture( "resources/ps3.png" )
   aTexXboxPad := LoadTexture( "resources/xbox.png" )

   SetConfigFlags( FLAG_MSAA_4X_HINT )

   SetTargetFPS( 60 )

   DO WHILE ! WindowShouldClose()

      BeginDrawing()

      ClearBackground( RAYWHITE )

      IF IsGamepadAvailable( 0 )

         DrawText( TextFormatSI( "GP1: %s", GetGamepadName( 0 ) ), 10, 10, 10, BLACK )

         IF TextIsEqual (GetGamepadName( 0 ), XBOX360_NAME_ID ) .OR. TextIsEqual (GetGamepadName( 0 ), XBOX360_LEGACY_NAME_ID )

            DrawTexture( aTexXboxPad, 0, 0, DARKGRAY )

            // Draw buttons: xbox home
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_MIDDLE )
               DrawCircle( 394, 89, 19, RED )
            ENDIF

            // Draw buttons: basic
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_MIDDLE_RIGHT )
               DrawCircle( 436, 150, 9, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_MIDDLE_LEFT )
               DrawCircle( 352, 150, 9, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT )
               DrawCircle( 501, 151, 15, BLUE )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN )
               DrawCircle( 536, 187, 15, LIME )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT )
               DrawCircle( 572, 151, 15, MAROON )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_UP )
               DrawCircle( 536, 115, 15, GOLD )
            ENDIF

            // Draw buttons: d-pad
            DrawRectangle( 317, 202, 19, 71, BLACK )
            DrawRectangle( 293, 228, 69, 19, BLACK )
            IF    IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_UP )
               DrawRectangle( 317, 202, 19, 26, RED )
            ENDIF
            IF  IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_DOWN )
               DrawRectangle( 317, 202 + 45, 19, 26, RED )
            ENDIF
            IF  IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_LEFT )
               DrawRectangle( 292, 228, 25, 19, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT )
               DrawRectangle( 292 + 44, 228, 26, 19, RED )
            ENDIF

            // Draw buttons: left-right back
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_TRIGGER_1 )
               DrawCircle( 259, 61, 20, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1 )
               DrawCircle( 536, 61, 20, RED )
            ENDIF

            // Draw axis: left joystick
            DrawCircle( 259, 152, 39, BLACK )
            DrawCircle( 259, 152, 34, LIGHTGRAY )
            DrawCircle( 259 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_X ) * 20 ), ;
               152 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_Y ) * 20 ), 25, BLACK )

            // Draw axis: right joystick
            DrawCircle( 461, 237, 38, BLACK )
            DrawCircle( 461, 237, 33, LIGHTGRAY )
            DrawCircle( 461 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_RIGHT_X ) * 20 ), ;
               237 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_RIGHT_Y ) * 20 ), 25, BLACK )

            // Draw axis: left-right triggers
            DrawRectangle( 170, 30, 15, 70, GRAY )
            DrawRectangle( 604, 30, 15, 70, GRAY )
            DrawRectangle( 170, 30, 15, 1 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_TRIGGER ) / 2 * 70 ), RED )
            DrawRectangle( 604, 30, 15, 1 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_RIGHT_TRIGGER ) / 2 * 70 ), RED )

         ELSEIF TextIsEqual (GetGamepadName( 0 ), PS3_NAME_ID )

            DrawTexture( aTexPs3Pad, 0, 0, DARKGRAY )

            // Draw buttons: ps
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_MIDDLE )
               DrawCircle( 396, 222, 13, RED )
            ENDIF
            // draw buttons: basic
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_MIDDLE_LEFT )
               DrawRectangle( 328, 170, 32, 13, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_MIDDLE_RIGHT )
               DrawTriangle( { 436, 168 }, { 436, 185 }, { 464, 177 }, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_UP )
               DrawCircle( 557, 144, 13, LIME )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT )
               DrawCircle( 586, 173, 13, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN )
               DrawCircle( 557, 203, 13, VIOLET )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT )
               DrawCircle( 527, 173, 13, PINK )
            ENDIF

            // Draw buttons: d-pad
            DrawRectangle( 225, 132, 24, 84, BLACK )
            DrawRectangle( 195, 161, 84, 25, BLACK )
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_UP )
               DrawRectangle( 225, 132, 24, 29, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_DOWN )
               DrawRectangle( 225, 132 + 54, 24, 30, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_LEFT )
               DrawRectangle( 195, 161, 30, 25, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT )
               DrawRectangle( 195 + 54, 161, 30, 25, RED )
            ENDIF

            // Draw buttons: left-right back buttons
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_TRIGGER_1 )
               DrawCircle( 239, 82, 20, RED )
            ENDIF
            IF IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1 )
               DrawCircle( 557, 82, 20, RED )
            ENDIF

            // Draw axis: left joystick
            DrawCircle( 319, 255, 35, BLACK )
            DrawCircle( 319, 255, 31, LIGHTGRAY )
            DrawCircle( 319 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_X ) * 20 ), ;
               255 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_Y ) * 20 ), 25, BLACK )

            // Draw axis: right joystick
            DrawCircle( 475, 255, 35, BLACK )
            DrawCircle( 475, 255, 31, LIGHTGRAY )
            DrawCircle( 475 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_RIGHT_X ) * 20 ), ;
               255 + Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_RIGHT_Y ) * 20 ), 25, BLACK )

            // Draw axis: left-right triggers
            DrawRectangle( 169, 48, 15, 70, GRAY )
            DrawRectangle( 611, 48, 15, 70, GRAY )
            DrawRectangle( 169, 48, 15, 1 - Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_TRIGGER ) / 2 * 70 ), RED )
            DrawRectangle( 611, 48, 15, 1 - Int( GetGamepadAxisMovement( 0, GAMEPAD_AXIS_RIGHT_TRIGGER ) / 2 * 70 ), RED )

         ELSE

            DrawText( "- GENERIC GAMEPAD -", 280, 180, 20, GRAY )
            // TODO: Draw generic gamepad
         ENDIF

         DrawText( TextFormat( "DETECTED AXIS [%i]:", GetGamepadAxisCount( 0 ) ), 10, 50, 10, MAROON )

         FOR i := 0 TO GetGamepadAxisCount( 0 ) - 1
            DrawText( TextFormatIF( "AXIS %i: %.02f", i, GetGamepadAxisMovement( 0, i ) ), 20, 70 + 20 * i, 10, DARKGRAY )
         NEXT

         IF GetGamepadButtonPressed() != -1
            DrawText( TextFormat( "DETECTED BUTTON: %i", GetGamepadButtonPressed() ), 10, 430, 10, RED )
         ELSE
            DrawText( "DETECTED BUTTON: NONE", 10, 430, 10, GRAY )
         ENDIF

      ELSE
         DrawText( "GP1: NOT DETECTED", 10, 10, 10, GRAY )

         DrawTexture( aTexXboxPad, 0, 0, LIGHTGRAY )
      ENDIF

      EndDrawing()

   ENDDO

   UnloadTexture( aTexPs3Pad )
   UnloadTexture( aTexXboxPad )

   CloseWindow()

   RETURN
