//Works Board ESP32 2.0.11, updated to 3.0.1 and stopped it from working, 2.0.17 no worky, 2.0.13 works
//Works Lib TFT_ESPI 2.5.34


#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <CST816S.h>

#define TOUCH_INT 4
#define TOUCH_SDA 18
#define TOUCH_SCL 17
#define TOUCH_RST 5

CST816S touch(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_INT);

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 280;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

//TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
TFT_eSPI tft = TFT_eSPI();

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
   // uint16_t touchX = 0, touchY = 0;
    //bool touched = false;//tft.getTouch( &touchX, &touchY, 600 );
    bool touched = touch.available();

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        //data->point.x = touchX;
        //data->point.y = touchY;

        int tmp = touch.data.y;
        touch.data.y = touch.data.x;
        touch.data.x = tmp;

        touch.data.x = 10+touch.data.x;  //0 =38,  should be 60
        touch.data.y = 230-touch.data.y; //230- =200

        data->point.x = touch.data.x;  
        data->point.y = touch.data.y;

        Serial.print( "Data x " );
        //Serial.println( touchX );
        Serial.println(touch.data.x);

        Serial.print( "Data y " );
        //Serial.println( touchY );
        Serial.println(touch.data.y);
    }
}

void setup()
{
    Serial.begin( 115200 ); 
    touch.begin();

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); 
#endif

    tft.begin();          
    tft.setRotation( 1 ); 

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );


    ui_init();

    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); 
    delay(5);
}
