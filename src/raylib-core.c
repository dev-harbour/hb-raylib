/*
 * RayLib library: raylib-core.c
 * version 3.7
 *
 * Copyright 2021 Leonardo Mendez ( mlmgerencir at gmail com )
 * Copyright 2020 - 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbraylib.h"

//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------

// Window-related functions

// void InitWindow(int width, int height, const char *title);  // Initialize window and OpenGL context
HB_FUNC( INITWINDOW )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_STRING )  != NULL )
   {
      InitWindow( hb_parni( 1 ), hb_parni( 2 ), hb_parc( 3 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool WindowShouldClose(void);                               // Check if KEY_ESCAPE pressed or Close icon pressed
HB_FUNC( WINDOWSHOULDCLOSE )
{
   hb_retl( WindowShouldClose() );
}

// void CloseWindow(void);                                     // Close window and unload OpenGL context
HB_FUNC( CLOSEWINDOW )
{
   CloseWindow();
}
// bool IsWindowReady(void);                                   // Check if window has been initialized successfully
HB_FUNC( ISWINDOWREADY )
{
   hb_retl( IsWindowReady() );
}

// bool IsWindowFullscreen(void);                              // Check if window is currently fullscreen
HB_FUNC( ISWINDOWFULLSCREEN )
{
   hb_retl( IsWindowFullscreen() );
}

// bool IsWindowHidden(void);                                  // Check if window is currently hidden (only PLATFORM_DESKTOP)
HB_FUNC( ISWINDOWHIDDEN )
{
   hb_retl( IsWindowHidden() );
}

// bool IsWindowMinimized(void);                               // Check if window is currently minimized (only PLATFORM_DESKTOP)
HB_FUNC( ISWINDOWMINIMIZED )
{
   hb_retl( IsWindowMinimized() );
}

// bool IsWindowMaximized(void);                               // Check if window is currently maximized (only PLATFORM_DESKTOP)
HB_FUNC( ISWINDOWMAXIMIZED )
{
   hb_retl( IsWindowMaximized() );
}

// bool IsWindowFocused(void);                                 // Check if window is currently focused (only PLATFORM_DESKTOP)
HB_FUNC( ISWINDOWFOCUSED )
{
   hb_retl( IsWindowFocused() );
}

// bool IsWindowResized(void);                                 // Check if window has been resized last frame
HB_FUNC( ISWINDOWRESIZED )
{
   hb_retl( IsWindowResized() );
}

// bool IsWindowState(unsigned int flag);                      // Check if one specific window flag is enabled
HB_FUNC( ISWINDOWSTATE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsWindowState( ( unsigned int ) hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetWindowState(unsigned int flags);                    // Set window configuration state using flags
HB_FUNC( SETWINDOWSTATE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetWindowState( ( unsigned int ) hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ClearWindowState(unsigned int flags);                  // Clear window configuration state flags
HB_FUNC( CLEARWINDOWSTATE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      ClearWindowState( ( unsigned int ) hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ToggleFullscreen(void);                                // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
HB_FUNC( TOGGLEFULLSCREEN )
{
   ToggleFullscreen();
}

// void MaximizeWindow(void);                                  // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
HB_FUNC( MAXIMIZEWINDOW )
{
   MaximizeWindow();
}

// void MinimizeWindow(void);                                  // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
HB_FUNC( MINIMIZEWINDOW )
{
   MinimizeWindow();
}

// void RestoreWindow(void);                                   // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
HB_FUNC( RESTOREWINDOW )
{
   RestoreWindow();
}

// void SetWindowIcon(Image image);                            // Set icon for window (only PLATFORM_DESKTOP)
HB_FUNC( SETWINDOWICON )
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

      SetWindowIcon( image );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetWindowTitle(const char *title);                     // Set title for window (only PLATFORM_DESKTOP)
HB_FUNC( SETWINDOWTITLE )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      SetWindowTitle( hb_parc( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetWindowPosition(int x, int y);                       // Set window position on screen (only PLATFORM_DESKTOP)
HB_FUNC( SETWINDOWPOSITION )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      SetWindowPosition( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetWindowMonitor(int monitor);                         // Set monitor for the current window (fullscreen mode)
HB_FUNC( SETWINDOWMONITOR )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetWindowMonitor( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetWindowMinSize(int width, int height);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
HB_FUNC( SETWINDOWMINSIZE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      SetWindowMinSize( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetWindowSize(int width, int height);                  // Set window dimensions
HB_FUNC( SETWINDOWSIZE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      SetWindowSize( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void *GetWindowHandle(void);                                // Get native window handle
HB_FUNC( GETWINDOWHANDLE )
{
   hb_retptr( GetWindowHandle() );
}

// int GetScreenWidth(void);                                   // Get current screen width
HB_FUNC( GETSCREENWIDTH )
{
   hb_retni( GetScreenWidth() );
}

// int GetScreenHeight(void);                                  // Get current screen height
HB_FUNC( GETSCREENHEIGHT )
{
   hb_retni( GetScreenHeight() );
}

// int GetMonitorCount(void);                                  // Get number of connected monitors
HB_FUNC( GETMONITORCOUNT )
{
   hb_retni( GetMonitorCount() );
}

// int GetCurrentMonitor(void);                                            // Get current connected monitor
HB_FUNC( GETCURRENTMONITOR )
{
   hb_retni( GetCurrentMonitor() );
}

// Vector2 GetMonitorPosition(int monitor);                    // Get specified monitor position
HB_FUNC( GETMONITORPOSITION )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      Vector2 vector2 = GetMonitorPosition( hb_parni( 1 ) );

      PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

      hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
      hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

      hb_itemReturnRelease( pVector2Array );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetMonitorWidth(int monitor);                           // Get specified monitor width
HB_FUNC( GETMONITORWIDTH )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetMonitorWidth( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetMonitorHeight(int monitor);                          // Get specified monitor height
HB_FUNC( GETMONITORHEIGHT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetMonitorHeight( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetMonitorPhysicalWidth(int monitor);                   // Get specified monitor physical width in millimetres
HB_FUNC( GETMONITORPHYSICALWIDTH )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetMonitorPhysicalWidth( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetMonitorPhysicalHeight(int monitor);                  // Get specified monitor physical height in millimetres
HB_FUNC( GETMONITORPHYSICALHEIGHT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetMonitorPhysicalHeight( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetMonitorRefreshRate(int monitor);                     // Get specified monitor refresh rate
HB_FUNC( GETMONITORREFRESHRATE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetMonitorRefreshRate( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Vector2 GetWindowPosition(void);                            // Get window position XY on monitor
HB_FUNC( GETWINDOWPOSITION )
{
   Vector2 vector2 = GetWindowPosition();

   PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

   hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
   hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

   hb_itemReturnRelease( pVector2Array );
}

// Vector2 GetWindowScaleDPI(void);                            // Get window scale DPI factor
HB_FUNC( GETWINDOWSCALEDPI )
{
   Vector2 vector2 = GetWindowScaleDPI();

   PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

   hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
   hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

   hb_itemReturnRelease( pVector2Array );
}

// const char *GetMonitorName(int monitor);                    // Get the human-readable, UTF-8 encoded name of the primary monitor
HB_FUNC( GETMONITORNAME )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retc( GetMonitorName( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetClipboardText(const char *text);                    // Set clipboard text content
HB_FUNC( SETCLIPBOARDTEXT )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      SetClipboardText( hb_parc( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetClipboardText(void);                         // Get clipboard text content
HB_FUNC( GETCLIPBOARDTEXT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retc( GetClipboardText() );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Custom frame control functions

// void SwapScreenBuffer(void);                                // Swap back buffer with front buffer (screen drawing)
HB_FUNC( SWAPSCREENBUFFER )
{
   SwapScreenBuffer();
}

// void PollInputEvents(void);                                 // Register all input events
HB_FUNC( POLLINPUTEVENTS )
{
   PollInputEvents();
}

// void WaitTime(float ms);                                    // Wait for some milliseconds (halt program execution)
HB_FUNC( WAITTIME )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      WaitTime( ( float ) hb_parnd( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Cursor-related functions

// void ShowCursor(void);                                      // Shows cursor
HB_FUNC( SHOWCURSOR )
{
   ShowCursor();
}

// void HideCursor(void);                                      // Hides cursor
HB_FUNC( HIDECURSOR )
{
   HideCursor();
}

// bool IsCursorHidden(void);                                  // Check if cursor is not visible
HB_FUNC( ISCURSORHIDDEN )
{
   hb_retl( IsCursorHidden() );
}

// void EnableCursor(void);                                    // Enables cursor (unlock cursor)
HB_FUNC( ENABLECURSOR )
{
   EnableCursor();
}

// void DisableCursor(void);                                   // Disables cursor (lock cursor)
HB_FUNC( DISABLECURSOR )
{
   DisableCursor();
}

// bool IsCursorOnScreen(void);                                // Check if cursor is on the current screen.
HB_FUNC( ISCURSORONSCREEN )
{
   hb_retl( IsCursorOnScreen() );
}

// Drawing-related functions

// void ClearBackground(Color color);                          // Set background color (framebuffer clear color)
HB_FUNC( CLEARBACKGROUND )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Color color;

      color.r = ( unsigned char ) hb_arrayGetNI( pItem, 1 );
      color.g = ( unsigned char ) hb_arrayGetNI( pItem, 2 );
      color.b = ( unsigned char ) hb_arrayGetNI( pItem, 3 );
      color.a = ( unsigned char ) hb_arrayGetNI( pItem, 4 );

      ClearBackground( color );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void BeginDrawing(void);                                    // Setup canvas (framebuffer) to start drawing
HB_FUNC( BEGINDRAWING )
{
   BeginDrawing();
}

// void EndDrawing(void);                                      // End canvas drawing and swap buffers (double buffering)
HB_FUNC( ENDDRAWING )
{
   EndDrawing();
}

// void BeginMode2D(Camera2D camera);                          // Initialize 2D mode with custom camera (2D)
HB_FUNC( BEGINMODE2D )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      Camera2D camera;

         //Vector2 offset
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem, 1 );

         camera.offset.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.offset.y = ( float ) hb_arrayGetND( pSubarray1, 2 );

         //Vector2 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );

      camera.rotation = ( float ) hb_arrayGetND( pItem, 3 );
      camera.zoom     = ( float ) hb_arrayGetND( pItem, 4 );

      BeginMode2D( camera );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void EndMode2D(void);                                       // Ends 2D mode with custom camera
HB_FUNC( ENDMODE2D )
{
   EndMode2D();
}


// void BeginMode3D(Camera3D camera);                          // Initializes 3D mode with custom camera (3D)
HB_FUNC( BEGINMODE3D )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Camera3D camera;

         // Vector3 position
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem, 1 );

         camera.position.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.position.y = ( float ) hb_arrayGetND( pSubarray1, 2 );
         camera.position.z = ( float ) hb_arrayGetND( pSubarray1, 3 );

         // Vector3 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );
         camera.target.z = ( float ) hb_arrayGetND( pSubarray2, 3 );

         // Vector3 up
         PHB_ITEM pSubarray3 = hb_arrayGetItemPtr( pItem, 3 );

         camera.up.x = ( float ) hb_arrayGetND( pSubarray3, 1 );
         camera.up.y = ( float ) hb_arrayGetND( pSubarray3, 2 );
         camera.up.z = ( float ) hb_arrayGetND( pSubarray3, 3 );

      camera.fovy = ( float ) hb_arrayGetND( pItem, 4 );
      camera.projection =     hb_arrayGetNI( pItem, 5 );

      BeginMode3D( camera );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void EndMode3D(void);                                       // Ends 3D mode and returns to default 2D orthographic mode
HB_FUNC( ENDMODE3D )
{
   EndMode3D();
}

// void BeginTextureMode(RenderTexture2D target);              // Initializes render texture for drawing
HB_FUNC( BEGINTEXTUREMODE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      RenderTexture2D target;

      target.id = ( unsigned int ) hb_arrayGetNI( pItem, 1 );

         // Texture texture
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem, 2 );

         target.texture.id      = ( unsigned int ) hb_arrayGetNI( pSubarray1, 1 );
         target.texture.width   =                  hb_arrayGetNI( pSubarray1, 2 );
         target.texture.height  =                  hb_arrayGetNI( pSubarray1, 3 );
         target.texture.mipmaps =                  hb_arrayGetNI( pSubarray1, 4 );
         target.texture.format  =                  hb_arrayGetNI( pSubarray1, 5 );

         // Texture depth
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem, 3 );

         target.depth.id      = ( unsigned int ) hb_arrayGetNI( pSubarray2, 1 );
         target.depth.width   =                  hb_arrayGetNI( pSubarray2, 2 );
         target.depth.height  =                  hb_arrayGetNI( pSubarray2, 3 );
         target.depth.mipmaps =                  hb_arrayGetNI( pSubarray2, 4 );
         target.depth.format  =                  hb_arrayGetNI( pSubarray2, 5 );

      BeginTextureMode( target );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void EndTextureMode(void);                                  // Ends drawing to render texture
HB_FUNC( ENDTEXTUREMODE )
{
   EndTextureMode();
}

//void BeginShaderMode(Shader shader);                                    // Begin custom shader drawing
//void EndShaderMode(void);                                               // End custom shader drawing (use default shader)

//void BeginBlendMode(int mode);                                          // Begin blending mode (alpha, additive, multiplied)
HB_FUNC( BEGINBLENDMODE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      BeginBlendMode( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void EndBlendMode(void);               // End blending mode (reset to default: alpha blending)
HB_FUNC( ENDBLENDMODE )
{
   EndBlendMode();
}

// void BeginScissorMode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
HB_FUNC( BEGINSCISSORMODE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL &&
       hb_param( 4, HB_IT_INTEGER ) != NULL )
   {
      BeginScissorMode( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void EndScissorMode(void);                                  // End scissor mode
HB_FUNC( ENDSCISSORMODE )
{
   EndScissorMode();
}

//void BeginVrStereoMode(VrStereoConfig config);                          // Begin stereo rendering
//void EndVrStereoMode(void);                                             // End stereo rendering

//VR stereo config functions for VR simulator

//VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device);                 // Load VR stereo config for VR simulator device parameters
//void UnloadVrStereoConfig(VrStereoConfig config);                       // Unload VR stereo config

//Shader management functions
//NOTE: Shader functionality is not available on OpenGL 1.1

//Shader LoadShader(const char *vsFileName, const char *fsFileName);                                  // Load shader from files and bind default locations
//Shader LoadShaderFromMemory(const char *vsCode, const char *fsCode);                                // Load shader from code strings and bind default locations
//int GetShaderLocation(Shader shader, const char *uniformName);                                      // Get shader uniform location
//int GetShaderLocationAttrib(Shader shader, const char *attribName);                                 // Get shader attribute location
//void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);               // Set shader uniform value
//void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count);   // Set shader uniform value vector
//void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);                                 // Set shader uniform value (matrix 4x4)
//void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture);                         // Set shader uniform value for texture (sampler2d)
//void UnloadShader(Shader shader);                                                                   // Unload shader from GPU memory (VRAM)

// Screen-space-related functions

// Ray GetMouseRay(Vector2 mousePosition, Camera camera);      // Returns a ray trace from mouse position
HB_FUNC( GETMOUSERAY )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 2 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 5 )
   {
      Vector2 mousePosition;

      mousePosition.x = ( float ) hb_arrayGetND( pItem1, 1 );
      mousePosition.y = ( float ) hb_arrayGetND( pItem1, 2 );

      Camera camera;

         // Vector3 position
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem2, 1 );

         camera.position.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.position.y = ( float ) hb_arrayGetND( pSubarray1, 2 );
         camera.position.z = ( float ) hb_arrayGetND( pSubarray1, 3 );

         // Vector3 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem2, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );
         camera.target.z = ( float ) hb_arrayGetND( pSubarray2, 3 );

         // Vector3 up
         PHB_ITEM pSubarray3 = hb_arrayGetItemPtr( pItem2, 3 );

         camera.up.x = ( float ) hb_arrayGetND( pSubarray3, 1 );
         camera.up.y = ( float ) hb_arrayGetND( pSubarray3, 2 );
         camera.up.z = ( float ) hb_arrayGetND( pSubarray3, 3 );

      camera.fovy = ( float ) hb_arrayGetND( pItem2, 4 );
      camera.projection =     hb_arrayGetNI( pItem2, 5 );

      Ray ray = GetMouseRay( mousePosition, camera );

      PHB_ITEM pRayArray = hb_itemArrayNew( 2 );

      // Vector3 position
      PHB_ITEM pSubarray1Vector3 = hb_arrayGetItemPtr( pRayArray, 1 );

      hb_arrayNew( pSubarray1Vector3, 3 );
      hb_arraySetND( pSubarray1Vector3, 1, ( float ) ray.position.x );
      hb_arraySetND( pSubarray1Vector3, 2, ( float ) ray.position.y );
      hb_arraySetND( pSubarray1Vector3, 3, ( float ) ray.position.z );

      // VectVector3or3 direction
      PHB_ITEM pSubarray2Vector3 = hb_arrayGetItemPtr( pRayArray, 2 );

      hb_arrayNew( pSubarray2Vector3, 3 );
      hb_arraySetND( pSubarray2Vector3, 1, ( float ) ray.direction.x );
      hb_arraySetND( pSubarray2Vector3, 2, ( float ) ray.direction.y );
      hb_arraySetND( pSubarray2Vector3, 3, ( float ) ray.direction.z );

      hb_itemReturnRelease( pRayArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Matrix GetCameraMatrix(Camera camera);                      // Returns camera transform matrix (view matrix)
// Matrix GetCameraMatrix2D(Camera2D camera);                  // Returns camera 2d transform matrix

// Vector2 GetWorldToScreen(Vector3 position, Camera camera);  // Returns the screen space position for a 3d world space position
HB_FUNC( GETWORLDTOSCREEN )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 3 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 5 )
   {
      Vector3 position;

      position.x = ( float ) hb_arrayGetND( pItem1, 1 );
      position.y = ( float ) hb_arrayGetND( pItem1, 2 );
      position.z = ( float ) hb_arrayGetND( pItem1, 3 );

      Camera camera;

         // Vector3 position
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem2, 1 );

         camera.position.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.position.y = ( float ) hb_arrayGetND( pSubarray1, 2 );
         camera.position.z = ( float ) hb_arrayGetND( pSubarray1, 3 );

         // Vector3 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem2, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );
         camera.target.z = ( float ) hb_arrayGetND( pSubarray2, 3 );

         // Vector3 up
         PHB_ITEM pSubarray3 = hb_arrayGetItemPtr( pItem2, 3 );

         camera.up.x = ( float ) hb_arrayGetND( pSubarray3, 1 );
         camera.up.y = ( float ) hb_arrayGetND( pSubarray3, 2 );
         camera.up.z = ( float ) hb_arrayGetND( pSubarray3, 3 );

      camera.fovy = ( float ) hb_arrayGetND( pItem2, 4 );
      camera.projection =     hb_arrayGetNI( pItem2, 5 );

      Vector2 vector2 = GetWorldToScreen( position, camera );

      PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

      hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
      hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

      hb_itemReturnRelease( pVector2Array );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); // Returns size position for a 3d world space position
HB_FUNC( GETWORLDTOSCREENEX )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 3 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 5 &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
                  hb_param( 4, HB_IT_INTEGER ) != NULL)
   {
      Vector3 position;

      position.x = ( float ) hb_arrayGetND( pItem1, 1 );
      position.y = ( float ) hb_arrayGetND( pItem1, 2 );
      position.z = ( float ) hb_arrayGetND( pItem1, 3 );

      Camera camera;

         // Vector3 position
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem2, 1 );

         camera.position.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.position.y = ( float ) hb_arrayGetND( pSubarray1, 2 );
         camera.position.z = ( float ) hb_arrayGetND( pSubarray1, 3 );

         // Vector3 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem2, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );
         camera.target.z = ( float ) hb_arrayGetND( pSubarray2, 3 );

         // Vector3 up
         PHB_ITEM pSubarray3 = hb_arrayGetItemPtr( pItem2, 3 );

         camera.up.x = ( float ) hb_arrayGetND( pSubarray3, 1 );
         camera.up.y = ( float ) hb_arrayGetND( pSubarray3, 2 );
         camera.up.z = ( float ) hb_arrayGetND( pSubarray3, 3 );

      camera.fovy = ( float ) hb_arrayGetND( pItem2, 4 );
      camera.projection =     hb_arrayGetNI( pItem2, 5 );

      Vector2 vector2 = GetWorldToScreenEx( position, camera, hb_parni( 3 ), hb_parni( 4 ) );

      PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

      hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
      hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

      hb_itemReturnRelease( pVector2Array );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}


// Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera); // Returns the screen space position for a 2d camera world space position
HB_FUNC( GETWORLDTOSCREEN2D )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 2 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem1, 1 );
      position.y = ( float ) hb_arrayGetND( pItem1, 2 );

      Camera2D camera;

         //Vector2 offset
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem1, 1 );

         camera.offset.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.offset.y = ( float ) hb_arrayGetND( pSubarray1, 2 );

         //Vector2 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem1, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );

      camera.rotation = ( float ) hb_arrayGetND( pItem1, 3 );
      camera.zoom     = ( float ) hb_arrayGetND( pItem1, 3 );

      Vector2 vector2 = GetWorldToScreen2D( position, camera );

      PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

      hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
      hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

      hb_itemReturnRelease( pVector2Array );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera); // Returns the world space position for a 2d camera screen space position
HB_FUNC( GETSCREENTOWORLD2D )
{
   PHB_ITEM pItem1, pItem2;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 2 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 )
   {
      Vector2 position;

      position.x = ( float ) hb_arrayGetND( pItem1, 1 );
      position.y = ( float ) hb_arrayGetND( pItem1, 2 );

      Camera2D camera;

         //Vector2 offset
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem1, 1 );

         camera.offset.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.offset.y = ( float ) hb_arrayGetND( pSubarray1, 2 );

         //Vector2 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem1, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );

      camera.rotation = ( float ) hb_arrayGetND( pItem1, 3 );
      camera.zoom     = ( float ) hb_arrayGetND( pItem1, 3 );

      Vector2 vector2 = GetScreenToWorld2D( position, camera );

      PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

      hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
      hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

      hb_itemReturnRelease( pVector2Array );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Timing-related functions

// void SetTargetFPS(int fps);                                 // Set target FPS (maximum)
HB_FUNC( SETTARGETFPS )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetTargetFPS( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetFPS(void);                                           // Returns current FPS
HB_FUNC( GETFPS )
{
   hb_retni( GetFPS() );
}

// float GetFrameTime(void);                                   // Returns time in seconds for last frame drawn
HB_FUNC( GETFRAMETIME )
{
   hb_retnd( ( float ) GetFrameTime() );
}

// double GetTime(void);                                       // Returns elapsed time in seconds since InitWindow()
HB_FUNC( GetTime )
{
   hb_retnd( GetTime() );
}

// Misc. functions

// int GetRandomValue(int min, int max);                       // Returns a random value between min and max (both included)
HB_FUNC( GETRANDOMVALUE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetRandomValue( hb_parni( 1 ), hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

//  void TakeScreenshot(const char *fileName);                         // Takes a screenshot of current screen (filename extension defines format)
HB_FUNC( TAKESCREENSHOT )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      TakeScreenshot( hb_parc( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetConfigFlags(unsigned int flags);                           // Setup init configuration flags (view FLAGS)
HB_FUNC( SETCONFIGFLAGS )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetConfigFlags( ( unsigned int ) hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void TraceLog(int logType, const char *text, ...);          // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR)
HB_FUNC( TRACELOG )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_STRING )  != NULL )
   {
      TraceLog( hb_parni( 1 ), hb_parc( 2 ), hb_parni( 3 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetTraceLogLevel(int logType);                             // Set the current threshold (minimum) log level
HB_FUNC( SETTRACELOGLEVEL )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetTraceLogLevel( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void *MemAlloc(int size);                                   // Internal memory allocator
HB_FUNC( MEMALLOC )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retptr( MemAlloc( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

//void *MemRealloc(void *ptr, int size);                                  // Internal memory reallocator

//void MemFree(void *ptr);                                                // Internal memory free
HB_FUNC( MEMFREE )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      MemFree( hb_parptr( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Set custom callbacks
// WARNING: Callbacks setup is intended for advance users

// void SetTraceLogCallback(TraceLogCallback callback);                    // Set custom trace log
// void SetLoadFileDataCallback(LoadFileDataCallback callback);            // Set custom file binary data loader
// void SetSaveFileDataCallback(SaveFileDataCallback callback);            // Set custom file binary data saver
// void SetLoadFileTextCallback(LoadFileTextCallback callback);            // Set custom file text data loader
// void SetSaveFileTextCallback(SaveFileTextCallback callback);            // Set custom file text data saver

// Files management functions

// unsigned char *LoadFileData(const char *fileName, unsigned int *bytesRead);     // Load file data as byte array (read)
HB_FUNC( LOADFILEDATA )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      unsigned int bytesRead;
      hb_retptr( ( unsigned char * ) LoadFileData( hb_parc( 1 ), &bytesRead ) );
      hb_storni( bytesRead, 1 );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UnloadFileData(unsigned char *data);                   // Unload file data allocated by LoadFileData()
HB_FUNC( UNLOADFILEDATA )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      UnloadFileData( ( unsigned char * ) hb_parptr( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool SaveFileData(const char *fileName, void *data, unsigned int bytesToWrite); // Save data to file from byte array (write), returns true on success
HB_FUNC( SAVEFILEDATA )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL && hb_param( 2, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( SaveFileData( hb_parc( 1 ), hb_parptr( 2 ), hb_parni( 3 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// char *LoadFileText(const char *fileName);                   // Load text data from file (read), returns a '\0' terminated string
HB_FUNC( LOADFILETEXT )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retc( LoadFileText( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UnloadFileText(char *text);                            // Unload file text data allocated by LoadFileText()
HB_FUNC( UNLOADFILETEXT )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      UnloadFileText( ( char * ) hb_parptr( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool SaveFileText(const char *fileName, char *text);        // Save text data to file (write), string must be '\0' terminated, returns true on success
HB_FUNC( SAVEFILETEXT )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_STRING ) != NULL )
   {
      char text = ( char ) hb_parni( 2 );
      hb_retl( SaveFileText( hb_parc( 1 ), &text ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool FileExists(const char *fileName);                      // Check if file exists
HB_FUNC( FILEEXISTS )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retl( FileExists( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool DirectoryExists(const char *dirPath);                  // Check if a directory path exists
HB_FUNC( DIRECTORYEXISTS )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retl( DirectoryExists( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsFileExtension(const char *fileName, const char *ext);// Check file extension (including point: .png, .wav)
HB_FUNC( ISFILEEXTENSION )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_STRING ) != NULL )
   {
      hb_retl( IsFileExtension( hb_parc( 1 ), hb_parc( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetFileExtension(const char *fileName);         // Get pointer to extension for a filename string (including point: ".png")
HB_FUNC( GETFILEEXTENSION )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retc( GetFileExtension( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetFileName(const char *filePath);              // Get pointer to filename for a path string
HB_FUNC( GETFILENAME )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retc( GetFileName( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetFileNameWithoutExt(const char *filePath);    // Get filename string without extension (uses static string)
HB_FUNC( GETFILENAMEWITHOUTEXT )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retc( GetFileNameWithoutExt( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetDirectoryPath(const char *filePath);         // Get full path for a given fileName with path (uses static string)
HB_FUNC( GETDIRECTORYPATH )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retc( GetDirectoryPath( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetPrevDirectoryPath(const char *dirPath);      // Get previous directory path for a given path (uses static string)
HB_FUNC( GETPREVDIRECTORYPATH )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retc( GetPrevDirectoryPath( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetWorkingDirectory(void);                      // Get current working directory (uses static string)
HB_FUNC( GETWORKINGDIRECTORY )
{
   hb_retc( GetWorkingDirectory() );
}

// char **GetDirectoryFiles(const char *dirPath, int *count);  // Get filenames in a directory path (memory should be freed)
HB_FUNC( GETDIRECTORYFILES )
{
   if( hb_param( 1, HB_IT_STRING  ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      int count;
      char ** files = GetDirectoryFiles( hb_parc( 1 ), &count );
      hb_storni( count, 1 );

      PHB_ITEM pFilesArray = hb_itemArrayNew( count );

      for( int i = 0; i < count; i++ )
      {
         hb_arraySetC( pFilesArray, i + 1, files[ i ] );
      }

      hb_itemReturnRelease( pFilesArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ClearDirectoryFiles(void);                             // Clear directory files paths buffers (free memory)
HB_FUNC( CLEARDIRECTORYFILES )
{
   ClearDirectoryFiles();
}

// bool ChangeDirectory(const char *dir);                      // Change working directory, return true on success
HB_FUNC( CHANGEDIRECTORY )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retnl( ChangeDirectory( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsFileDropped(void);                                   // Check if a file has been dropped into window
HB_FUNC( ISFILEDROPPED )
{
   hb_retl( IsFileDropped() );
}

// char **GetDroppedFiles(int *count);                         // Get dropped files names (memory should be freed)
HB_FUNC( GETDROPPEDFILES )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      int count;
      char ** files = GetDroppedFiles( &count );
      hb_storni( count, 1 );

      PHB_ITEM pFilesArray = hb_itemArrayNew( count );

      for( int i = 0; i < count; i++ )
      {
         hb_arraySetC( pFilesArray, i + 1, files[ i ] );
      }

      hb_itemReturnRelease( pFilesArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void ClearDroppedFiles(void);                               // Clear dropped files paths buffer (free memory)
HB_FUNC( CLEARDROPPEDFILES )
{
   ClearDroppedFiles();
}

// long GetFileModTime(const char *fileName);                  // Get file modification time (last write time)
HB_FUNC( GETFILEMODTIME )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retnl( GetFileModTime( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned char *CompressData(unsigned char *data, int dataLength, int *compDataLength);        // Compress data (DEFLATE algorithm)
HB_FUNC( COMPRESSDATA )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      int compDataLength;
      hb_retptr( ( unsigned char * ) CompressData( ( unsigned char * ) hb_parptr( 1 ), hb_parni( 2 ), &compDataLength ) );
      hb_storni( compDataLength, 3 );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned char *DecompressData(unsigned char *compData, int compDataLength, int *dataLength);  // Decompress data (DEFLATE algorithm)
HB_FUNC( DECOMPRESSDATA )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      int dataLength;
      hb_retptr( ( unsigned char * ) DecompressData( ( unsigned char * ) hb_parptr( 1 ), hb_parni( 2 ), &dataLength ) );
      hb_storni( dataLength, 3 );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Persistent storage management

// bool SaveStorageValue(unsigned int position, int value);    // Save integer value to storage file (to defined position), returns true on success
HB_FUNC( SAVESTORAGEVALUE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      SaveStorageValue( ( unsigned int) hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int LoadStorageValue(unsigned int position);                // Load integer value from storage file (from defined position)
HB_FUNC( LOADSTORAGEVALUE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( LoadStorageValue( ( unsigned int ) hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void OpenURL(const char *url);                              // Open URL with default system browser (if available)
HB_FUNC( OPENURL )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      OpenURL( hb_parc( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard

// bool IsKeyPressed(int key);                             // Detect if a key has been pressed once
HB_FUNC( ISKEYPRESSED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsKeyPressed( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsKeyDown(int key);                                // Detect if a key is being pressed
HB_FUNC( ISKEYDOWN )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsKeyDown( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsKeyReleased(int key);                            // Detect if a key has been released once
HB_FUNC( ISKEYRELEASED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsKeyReleased( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsKeyUp(int key);                                  // Detect if a key is NOT being pressed
HB_FUNC( ISKEYUP )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsKeyUp( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)
HB_FUNC( SETEXITKEY )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetExitKey( hb_parni( 1 ) ) ;
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued
HB_FUNC( GETKEYPRESSED )
{
   hb_retni( GetKeyPressed() );
}

// int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued
HB_FUNC( GETCHARPRESSED )
{
   hb_retni( GetCharPressed() );
}

// Input-related functions: gamepads

// bool IsGamepadAvailable(int gamepad);                   // Detect if a gamepad is available
HB_FUNC( ISGAMEPADAVAILABLE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsGamepadAvailable( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char *GetGamepadName(int gamepad);                // Return gamepad internal name id
HB_FUNC( GETGAMEPADNAME )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retc( GetGamepadName( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsGamepadButtonPressed(int gamepad, int button);   // Detect if a gamepad button has been pressed once
HB_FUNC( ISGAMEPADBUTTONPRESSED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsGamepadButtonPressed( hb_parni( 1 ), hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsGamepadButtonDown(int gamepad, int button);      // Detect if a gamepad button is being pressed
HB_FUNC( ISGAMEPADBUTTONDOWN )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsGamepadButtonDown( hb_parni( 1 ), hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsGamepadButtonReleased(int gamepad, int button);  // Detect if a gamepad button has been released once
HB_FUNC( ISGAMEPADBUTTONRELEASED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsGamepadButtonReleased( hb_parni( 1 ), hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsGamepadButtonUp(int gamepad, int button);        // Detect if a gamepad button is NOT being pressed
HB_FUNC( ISGAMEPADBUTTONUP )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsGamepadButtonUp( hb_parni( 1 ), hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetGamepadButtonPressed(void);                      // Get the last gamepad button pressed
HB_FUNC( GETGAMEPADBUTTONPRESSED )
{
   hb_retni( GetGamepadButtonPressed() );
}

// int GetGamepadAxisCount(int gamepad);                   // Return gamepad axis count for a gamepad
HB_FUNC( GETGAMEPADAXISCOUNT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( GetGamepadAxisCount( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float GetGamepadAxisMovement(int gamepad, int axis);    // Return axis movement value for a gamepad axis
HB_FUNC( GETGAMEPADAXISMOVEMENT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retnd( ( float ) GetGamepadAxisMovement( hb_parni( 1 ), hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int SetGamepadMappings(const char *mappings);                           // Set internal gamepad mappings (SDL_GameControllerDB)
HB_FUNC( SETGAMEPADMAPPINGS )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retni( SetGamepadMappings( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Input-related functions: mouse

// bool IsMouseButtonPressed(int button);                  // Detect if a mouse button has been pressed once
HB_FUNC( ISMOUSEBUTTONPRESSED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsMouseButtonPressed( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsMouseButtonDown(int button);                     // Detect if a mouse button is being pressed
HB_FUNC( ISMOUSEBUTTONDOWN )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsMouseButtonDown( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsMouseButtonReleased(int button);                 // Detect if a mouse button has been released once
HB_FUNC( ISMOUSEBUTTONRELEASED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsMouseButtonReleased( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsMouseButtonUp(int button);                       // Detect if a mouse button is NOT being pressed
HB_FUNC( ISMOUSEBUTTONUP )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsMouseButtonUp( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetMouseX(void);                                    // Returns mouse position X
HB_FUNC( GETMOUSEX )
{
   hb_retni( GetMouseX() );
}

// int GetMouseY(void);                                    // Returns mouse position Y
HB_FUNC( GETMOUSEY )
{
   hb_retni( GetMouseY() );
}

// Vector2 GetMousePosition(void);                         // Returns mouse position XY
HB_FUNC( GETMOUSEPOSITION )
{
   Vector2 vector2 = GetMousePosition();

   PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

   hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
   hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

   hb_itemReturnRelease( pVector2Array );
}

// Vector2 GetMouseDelta(void);                            // Get mouse delta between frames

// void SetMousePosition(int x, int y);                    // Set mouse position XY
HB_FUNC( SETMOUSEPOSITION )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      SetMousePosition( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetMouseOffset(int offsetX, int offsetY);          // Set mouse offset
HB_FUNC( SETMOUSEOFFSET )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      SetMouseOffset( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetMouseScale(float scaleX, float scaleY);         // Set mouse scaling
HB_FUNC( SETMOUSESCALE )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL &&
       hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      SetMouseScale( ( float ) hb_parnd( 1 ), ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float GetMouseWheelMove(void);                          // Returns mouse wheel movement Y
HB_FUNC( GETMOUSEWHEELMOVE )
{
   hb_retni( GetMouseWheelMove() );
}

// void SetMouseCursor(int cursor);                        // Set mouse cursor
HB_FUNC( SETMOUSECURSOR )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetMouseCursor( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Input-related functions: touch

// int GetTouchX(void);                                    // Returns touch position X for touch point 0 (relative to screen size)
HB_FUNC( GetTouchX )
{
   hb_retni( GetTouchX() );
}

// int GetTouchY(void);                                    // Returns touch position Y for touch point 0 (relative to screen size)
HB_FUNC( GETTOUCHY )
{
   hb_retni( GetTouchY() );
}

// Vector2 GetTouchPosition(int index);                    // Returns touch position XY for a touch point index (relative to screen size)
HB_FUNC( GETTOUCHPOSITION )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      Vector2 vector2 = GetTouchPosition( hb_parni( 1 ) );

      PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

      hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
      hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

      hb_itemReturnRelease( pVector2Array );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetTouchPointCount(void);                           // Get number of touch points
HB_FUNC( GETTOUCHPOINTCOUNT )
{
   hb_retni( GetTouchPointCount() );
}

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: gestures)
//------------------------------------------------------------------------------------

// void SetGesturesEnabled(unsigned int gestureFlags);     // Enable a set of gestures using flags
HB_FUNC( SETGESTURESENABLED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetGesturesEnabled( ( unsigned int ) hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// bool IsGestureDetected(int gesture);                    // Check if a gesture have been detected
HB_FUNC( ISGESTUREDETECTED )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( IsGestureDetected( hb_parni( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// int GetGestureDetected(void);                           // Get latest detected gesture
HB_FUNC( GETGESTUREDETECTED )
{
   hb_retni( GetGestureDetected() );
}

// float GetGestureHoldDuration(void);                     // Get gesture hold time in milliseconds
HB_FUNC( GETGESTUREHOLDDURATION )
{
   hb_retnd( ( float ) GetGestureHoldDuration() );
}

// Vector2 GetGestureDragVector(void);                     // Get gesture drag vector
HB_FUNC( GETGESTUREDRAGVECTOR )
{
   Vector2 vector2 = GetGestureDragVector();

   PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

   hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
   hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

   hb_itemReturnRelease( pVector2Array );
}

// float GetGestureDragAngle(void);                        // Get gesture drag angle
HB_FUNC( GETGESTUREDRAGANGLE )
{
   hb_retnd( ( float ) GetGestureDragAngle() );
}

// Vector2 GetGesturePinchVector(void);                    // Get gesture pinch delta
HB_FUNC( GETGESTUREPINCHVECTOR )
{
   Vector2 vector2 = GetGesturePinchVector();

   PHB_ITEM pVector2Array = hb_itemArrayNew( 2 );

   hb_arraySetNI( pVector2Array, 1, ( float ) vector2.x );
   hb_arraySetNI( pVector2Array, 2, ( float ) vector2.y );

   hb_itemReturnRelease( pVector2Array );
}

// float GetGesturePinchAngle(void);                       // Get gesture pinch angle
HB_FUNC( GETGESTUREPINCHANGLE )
{
   hb_retnd( ( float ) GetGesturePinchAngle() );
}

//------------------------------------------------------------------------------------
// Camera System Functions (Module: camera)
//------------------------------------------------------------------------------------

// void SetCameraMode(Camera camera, int mode);                // Set camera mode (multiple camera modes available)

HB_FUNC( SETCAMERAMODE )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 &&
                 hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      Camera camera;

         // Vector3 position
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem, 1 );

         camera.position.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.position.y = ( float ) hb_arrayGetND( pSubarray1, 2 );
         camera.position.z = ( float ) hb_arrayGetND( pSubarray1, 3 );

         // Vector3 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );
         camera.target.z = ( float ) hb_arrayGetND( pSubarray2, 3 );

         // Vector3 up
         PHB_ITEM pSubarray3 = hb_arrayGetItemPtr( pItem, 3 );

         camera.up.x = ( float ) hb_arrayGetND( pSubarray3, 1 );
         camera.up.y = ( float ) hb_arrayGetND( pSubarray3, 2 );
         camera.up.z = ( float ) hb_arrayGetND( pSubarray3, 3 );

      camera.fovy = ( float ) hb_arrayGetND( pItem, 4 );
      camera.projection =     hb_arrayGetNI( pItem, 5 );

      SetCameraMode( camera, hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void UpdateCamera(Camera *camera);                          // Update camera position for selected mode
HB_FUNC( UPDATECAMERA )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 5 )
   {
      Camera camera;

         // Vector3 position
         PHB_ITEM pSubarray1 = hb_arrayGetItemPtr( pItem, 1 );

         camera.position.x = ( float ) hb_arrayGetND( pSubarray1, 1 );
         camera.position.y = ( float ) hb_arrayGetND( pSubarray1, 2 );
         camera.position.z = ( float ) hb_arrayGetND( pSubarray1, 3 );

         // Vector3 target
         PHB_ITEM pSubarray2 = hb_arrayGetItemPtr( pItem, 2 );

         camera.target.x = ( float ) hb_arrayGetND( pSubarray2, 1 );
         camera.target.y = ( float ) hb_arrayGetND( pSubarray2, 2 );
         camera.target.z = ( float ) hb_arrayGetND( pSubarray2, 3 );

         // Vector3 up
         PHB_ITEM pSubarray3 = hb_arrayGetItemPtr( pItem, 3 );

         camera.up.x = ( float ) hb_arrayGetND( pSubarray3, 1 );
         camera.up.y = ( float ) hb_arrayGetND( pSubarray3, 2 );
         camera.up.z = ( float ) hb_arrayGetND( pSubarray3, 3 );

      camera.fovy = ( float ) hb_arrayGetND( pItem, 4 );
      camera.projection =     hb_arrayGetNI( pItem, 5 );

      UpdateCamera( &camera );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetCameraPanControl(int keyPan);                       // Set camera pan key to combine with mouse movement (free camera)
HB_FUNC( SETCAMERAPANCONTROL )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetCameraPanControl( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetCameraAltControl(int keyAlt);                       // Set camera alt key to combine with mouse movement (free camera)
HB_FUNC( SETCAMERAALTCONTROL )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetCameraAltControl( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetCameraSmoothZoomControl(int keySmoothZoom);         // Set camera smooth zoom key to combine with mouse (free camera)
HB_FUNC( SETCAMERASMOOTHZOOMCONTROL )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      SetCameraSmoothZoomControl( hb_parni( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void SetCameraMoveControls(int keyFront, int keyBack, int keyRight, int keyLeft, int keyUp, int keyDown); // Set camera move controls (1st person and 3rd person cameras)
HB_FUNC( SetCameraMoveControls )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL &&
       hb_param( 4, HB_IT_INTEGER ) != NULL &&
       hb_param( 5, HB_IT_INTEGER ) != NULL &&
       hb_param( 6, HB_IT_INTEGER ) != NULL )
   {
      SetCameraMoveControls( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ), hb_parni( 6 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
