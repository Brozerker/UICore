#include "libraries.h"

using namespace std;

const int SCREEN_WIDTH    = 800;
const int SCREEN_HEIGHT   = 600;
const int SCREEN_BPP      = 32;

HWND                 g_hWnd       = NULL;
LPDIRECT3D9          g_pD3D       = NULL;
LPDIRECT3DDEVICE9    g_pd3dDevice = NULL;
LPDIRECTINPUT8       g_lpdi       = NULL;
LPDIRECTINPUTDEVICE8 g_pKeyboard  = NULL;

RECT  g_rcWindow;
RECT  g_rcViewport;
RECT  g_rcScreen;
BOOL  g_bWindowed       = true;
BOOL  g_bActive         = false;

DWORD LAST_FIRE_TICK	= 0;
int   SCORE_BOARD       = 0;
int   HEALTH_BAR		= 9;

double ELAPSED_TIME;
double CURRENT_TIME;
double END_TIME;
double ANIMATION_TIMER = 0.0;

struct PARTICLE
{
    int  x;
    int  y;
    int  nVelocity;
    bool bVisible;
    COLORREF color; 
};

int RandomInt( int a_Low, int a_High )
{
    int Range = a_High - a_Low;
    int Num = rand() % Range;
    return( Num + a_Low );
}


typedef list<CSprite> SPRITELIST;

SPRITELIST				SPRITE_LIST;
SPRITELIST::iterator	SPRITE_A;
SPRITELIST::iterator	SPRITE_B;
SPRITELIST::iterator	SPRITE_C;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT WinInit(HINSTANCE hInst, int nCmdShow, HWND* phWnd, HACCEL* phAccel);
HRESULT GameStart(HWND hWnd);
HRESULT GameMain(HWND hWnd);

HRESULT InitDirect3D(HWND hWnd, BOOL bWindowed);
void    FreeDirect3D(void);
HRESULT InitDirectInput(HWND hWnd);
void    FreeDirectInput(void);
void    InitializeSprites(void);

void    ShipScore(void);
HRESULT DisplayFrame(void);
HRESULT ShipHealthBar(void);
int     RandomInt(int a_Low, int a_High);


int APIENTRY WinMain( HINSTANCE hInst, 
                      HINSTANCE hPrevInst, 
                      LPSTR     pCmdLine, 
                      int       nCmdShow )
{
    MSG    msg;
    HWND   hWnd;
    HACCEL hAccel;

    memset(&msg,0,sizeof(msg));
    
    WinInit( hInst, nCmdShow, &hWnd, &hAccel );

    GameStart( hWnd );

    while( TRUE )
    {

        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( 0 == GetMessage(&msg, NULL, 0, 0 ) )
            {

                return (int)msg.wParam;
            }

  
            if( 0 == TranslateAccelerator( hWnd, hAccel, &msg ) )
            {
                TranslateMessage( &msg ); 
                DispatchMessage( &msg );
            }
        }
        else
        {
            if( g_bActive )
            {


                CURRENT_TIME     = timeGetTime();
                ELAPSED_TIME = ((CURRENT_TIME - END_TIME) * 0.001);
                END_TIME    = CURRENT_TIME;

                if( FAILED( GameMain( hWnd ) ) )
                {


                    MessageBox( hWnd, TEXT("GameMain() failed. ")
                        TEXT("The game will now exit. "), TEXT("PrototypeX"), 
                        MB_ICONERROR | MB_OK );
                    return FALSE;
                }
            }
            else
            {

                WaitMessage();


            }
        }
    }
}


HRESULT WinInit( HINSTANCE hInst, int nCmdShow, HWND *phWnd, HACCEL *phAccel )
{
    WNDCLASSEX wc;
    HWND       hWnd;
    HACCEL     hAccel;

    wc.cbSize        = sizeof(wc);
    wc.lpszClassName = TEXT("MY_WINDOWS_CLASS");
    wc.lpfnWndProc   = MainWndProc;
    wc.style         = CS_VREDRAW | CS_HREDRAW;
    wc.hInstance     = hInst;
    wc.hIcon         = LoadIcon( hInst, MAKEINTRESOURCE(IDI_MAIN_ICON) );
    wc.hIconSm       = LoadIcon( hInst, MAKEINTRESOURCE(IDI_MAIN_ICON) );
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;

    if( RegisterClassEx( &wc ) == 0 )
        return E_FAIL;


    hAccel = LoadAccelerators( hInst, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );


    DWORD dwFrameWidth    = GetSystemMetrics( SM_CXSIZEFRAME );
    DWORD dwFrameHeight   = GetSystemMetrics( SM_CYSIZEFRAME );
    DWORD dwMenuHeight    = GetSystemMetrics( SM_CYMENU );
    DWORD dwCaptionHeight = GetSystemMetrics( SM_CYCAPTION );
    DWORD dwWindowWidth   = SCREEN_WIDTH  + dwFrameWidth * 2;
    DWORD dwWindowHeight  = SCREEN_HEIGHT + dwFrameHeight * 2 + 
                            dwMenuHeight + dwCaptionHeight;


    DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX;
    hWnd = CreateWindowEx( 0, TEXT("MY_WINDOWS_CLASS"), 
                           TEXT("2.5D Space Shooter"),
                           dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
                           dwWindowWidth, dwWindowHeight, NULL, NULL, hInst, NULL );
    if( hWnd == NULL )
        return E_FAIL;

    ShowWindow( hWnd, nCmdShow );
    UpdateWindow( hWnd );

    GetWindowRect( hWnd, &g_rcWindow );

    *phWnd   = hWnd;
    *phAccel = hAccel;

    return S_OK;
}


LRESULT CALLBACK MainWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDM_TOGGLEFULLSCREEN:
                    return 0L;

                case IDM_EXIT:

                    PostMessage( hWnd, WM_CLOSE, 0, 0 );
                    return 0L;
            }
            break;

        case WM_GETMINMAXINFO:
            {

                MINMAXINFO* pMinMax = (MINMAXINFO*) lParam;

                DWORD dwFrameWidth    = GetSystemMetrics( SM_CXSIZEFRAME );
                DWORD dwFrameHeight   = GetSystemMetrics( SM_CYSIZEFRAME );
                DWORD dwMenuHeight    = GetSystemMetrics( SM_CYMENU );
                DWORD dwCaptionHeight = GetSystemMetrics( SM_CYCAPTION );

                pMinMax->ptMinTrackSize.x = SCREEN_WIDTH  + dwFrameWidth * 2;
                pMinMax->ptMinTrackSize.y = SCREEN_HEIGHT + dwFrameHeight * 2 + 
                                            dwMenuHeight + dwCaptionHeight;

                pMinMax->ptMaxTrackSize.x = pMinMax->ptMinTrackSize.x;
                pMinMax->ptMaxTrackSize.y = pMinMax->ptMinTrackSize.y;
            }
            return 0L;

        case WM_SIZE:

            if( SIZE_MAXHIDE == wParam || SIZE_MINIMIZED == wParam )
                g_bActive = FALSE;
            else
                g_bActive = TRUE;
            break;

        case WM_SETCURSOR:

            if( !g_bWindowed )
            {
                SetCursor( NULL );
                return TRUE;
            }
            break;

        case WM_EXITMENULOOP:

            break;

        case WM_EXITSIZEMOVE:

            break;

        case WM_SYSCOMMAND:

            switch( wParam )
            {
                case SC_MOVE:
                case SC_SIZE:
                case SC_MAXIMIZE:
                case SC_MONITORPOWER:
                    if( !g_bWindowed )
                        return TRUE;
            }
            break;
            
        case WM_ACTIVATE:
            if( WA_INACTIVE != wParam && g_pKeyboard )
            {

                g_pKeyboard->Acquire();
            }

            break;

        case WM_DESTROY:

            PostQuitMessage( 0 );
            return 0L;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}


HRESULT GameStart( HWND hWnd )
{
    HRESULT hr;

    if( FAILED( hr = InitDirect3D( hWnd, g_bWindowed ) ) )
        return hr;

    InitializeSprites();

    LAST_FIRE_TICK = timeGetTime();

    return S_OK;
}

HRESULT GameMain( HWND hWnd )
{
    ANIMATION_TIMER += ELAPSED_TIME;

    if( ANIMATION_TIMER >= 0.016 )
        ANIMATION_TIMER = 0.0;
    else
        return S_OK;

    ShipScore();

    DisplayFrame();

    return S_OK;
}


HRESULT InitDirect3D( HWND hWnd, BOOL bWindowed )
{
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

    D3DCAPS9 d3dCaps;
    g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps );

    D3DDISPLAYMODE d3ddm;
    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );

    if( bWindowed == TRUE )
    {
        d3dpp.Windowed         = TRUE;
        d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
        d3dpp.BackBufferFormat = d3ddm.Format;
    }
    else
    {
        d3dpp.Windowed         = FALSE;
        d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
        d3dpp.BackBufferWidth  = SCREEN_WIDTH;
        d3dpp.BackBufferHeight = SCREEN_HEIGHT;
        d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    }

    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    d3dpp.Flags                  = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                          D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                          &d3dpp, &g_pd3dDevice );

    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 
                                SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f );

    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    return S_OK;
}

void InitializeSprites(void)
{
    CSprite sprite;
    int i = 0;

	//RED HEALTH (FIRST)
    sprite.zeroSpriteValues();
    wcscpy_s( sprite.m_spriteType, L"redHP" );
    wcscpy_s( sprite.m_textureName, L"misc.bmp" );
    sprite.m_spriteW				= 200;
    sprite.m_spriteH				= 200;
    sprite.m_isActive				= false;
    sprite.m_oneFrame				= true;
    sprite.m_offsetX				= 51;
    sprite.m_offsetY				= 0;
    sprite.m_frameW					= 30;
    sprite.m_frameH					= 40;

    SPRITE_LIST.push_back(sprite);

	//YELLOW HEALTH (SECOND)
    sprite.zeroSpriteValues();
    wcscpy_s( sprite.m_spriteType, L"yellowHP" );
    wcscpy_s( sprite.m_textureName, L"misc.bmp" );
    sprite.m_spriteW				= 200;
    sprite.m_spriteH				= 200;
    sprite.m_isActive				= false;
    sprite.m_oneFrame				= true;
    sprite.m_offsetX				= 81;
    sprite.m_offsetY				= 0;
    sprite.m_frameW					= 30;
    sprite.m_frameH					= 40;
    
    SPRITE_LIST.push_back(sprite);

	//GREEN HEALTH (THIRD)
    sprite.zeroSpriteValues();
    wcscpy_s( sprite.m_spriteType, L"greenHP" );
    wcscpy_s( sprite.m_textureName, L"misc.bmp" );
    sprite.m_spriteW				= 200;
    sprite.m_spriteH				= 200;
    sprite.m_isActive				= false;
    sprite.m_oneFrame				= true;
    sprite.m_offsetX				= 111;
    sprite.m_offsetY				= 0;
    sprite.m_frameW					= 30;
    sprite.m_frameH					= 40;

    SPRITE_LIST.push_back(sprite);

	//SCORE NUMBER FONT
    for( i = 0; i < 4; i++ )
    {
        sprite.zeroSpriteValues();
        wcscpy_s( sprite.m_spriteType, L"numbers" );
        wcscpy_s( sprite.m_textureName, L"numbers.bmp" );
        sprite.m_spriteW             = 185;
        sprite.m_spriteH             = 27;
        sprite.m_State			     = i;
        sprite.m_posX				 = (float)600 + (i * 17);
        sprite.m_posY				 = 572;
        sprite.m_frameAnimate        = false;
        sprite.m_offsetX			 =  9;
        sprite.m_offsetY			 =  5;
        sprite.m_frameAcross         = 10;
        sprite.m_frameW				 = 17;
        sprite.m_frameH				 = 17;
        sprite.loadAnimationString( 0, "0 1 2 3 4 5 6 7 8 9", CSprite::LOOP_ANIMATION );

        SPRITE_LIST.push_back(sprite);
    }
}

void ShipScore(void)
{

	int number4 = SCORE_BOARD % 10; 
    int number3 = (SCORE_BOARD % 100)/10;
    int number2 = (SCORE_BOARD % 1000)/100;
    int number1 = (SCORE_BOARD % 10000)/1000;

    for( SPRITE_A = SPRITE_LIST.begin(); SPRITE_A != SPRITE_LIST.end(); ++SPRITE_A )
    {
        if( !lstrcmp(SPRITE_A->m_spriteType, L"numbers") )
        {
            if( SPRITE_A->m_State == 0 )
                SPRITE_A->m_CurrFrame = number1;

            if( SPRITE_A->m_State == 1 )
                SPRITE_A->m_CurrFrame = number2;

            if( SPRITE_A->m_State == 2 )
                SPRITE_A->m_CurrFrame = number3;

            if( SPRITE_A->m_State == 3 )
                SPRITE_A->m_CurrFrame = number4;
        }

    }
}

HRESULT DisplayFrame()
{
    HRESULT hr;

    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0 );

    g_pd3dDevice->BeginScene();

    ShipHealthBar();

    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    for( SPRITE_A = SPRITE_LIST.begin(); SPRITE_A != SPRITE_LIST.end(); ++SPRITE_A )
	{
        SPRITE_A->drawSprite( g_pd3dDevice );
	}
    g_pd3dDevice->EndScene();

    if( FAILED( hr = g_pd3dDevice->Present( NULL, NULL, NULL, NULL ) ) )
	{
        return hr;
	}
    return S_OK;
}

HRESULT ShipHealthBar( void )
{

    int healthPosX	= 260;
    int healthPosY	= 550;
    int markSpace	= 30;
    int markCount   = 0;
    int marksRed    = 3;
    int marksYellow = 3;
    int marksGreen  = 3;
    int i			= 0;

    for( SPRITE_A = SPRITE_LIST.begin(); SPRITE_A != SPRITE_LIST.end(); ++SPRITE_A )
    {
        if( !lstrcmp(SPRITE_A->m_spriteType, L"HealthBar") )
        {
            SPRITE_A->m_isActive = true;

            SPRITE_A->m_posX = (float)healthPosX - 3;
            SPRITE_A->m_posY = (float)healthPosY - 2;
            SPRITE_A->drawSprite( g_pd3dDevice );

            SPRITE_A->m_isActive = false;
        }

        if( !lstrcmp(SPRITE_A->m_spriteType, L"redHP") )
        {
            SPRITE_A->m_isActive = true;

            if( HEALTH_BAR > 0 )
            {
                for( i = 0; i < marksRed; ++i )
                {
                    SPRITE_A->m_posX = (float)healthPosX;
                    SPRITE_A->m_posY = (float)healthPosY;
                    SPRITE_A->drawSprite( g_pd3dDevice );

                    healthPosX += markSpace;
                    ++ markCount;

                    if( markCount >= HEALTH_BAR )
                        break;
                }
            }

            SPRITE_A->m_isActive = false;
        }

        if( !lstrcmp(SPRITE_A->m_spriteType, L"yellowHP") )
        {

            SPRITE_A->m_isActive = true;

            if( HEALTH_BAR > marksYellow )
            {
                for( i = 0; i < marksYellow; ++i )
                {
                    SPRITE_A->m_posX = (float)healthPosX;
                    SPRITE_A->m_posY = (float)healthPosY;
                    SPRITE_A->drawSprite( g_pd3dDevice );

                    healthPosX += markSpace;
                    ++ markCount;

                    if( markCount >= HEALTH_BAR )
                        break;
                }
            }

            SPRITE_A->m_isActive = false;
        }

        if( !lstrcmp(SPRITE_A->m_spriteType, L"greenHP") )
        {
            SPRITE_A->m_isActive = true;

            if( HEALTH_BAR > marksGreen )
            {
                for( i = 0; i < marksGreen; ++i )
                {
                    SPRITE_A->m_posX = (float)healthPosX;
                    SPRITE_A->m_posY = (float)healthPosY;
                    SPRITE_A->drawSprite( g_pd3dDevice );

                    healthPosX += markSpace;
                    ++markCount;

                    if( markCount >= HEALTH_BAR )
                        break;
                }
            }

            SPRITE_A->m_isActive = false;
            break;
        }
    }

    return S_OK;
}

