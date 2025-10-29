/*
 * File:   main.c
 * Author: snidg
 *
 * Created on 21 May, 2025, 10:26 PM
 */


#include <xc.h>
#include "can.h"
#include "clcd.h"
#include "main.h"

void config(void) {
   
    init_clcd();
    clcd_print("G SP TEMP RPM  I",LINE1(0));
     init_can();
}
unsigned int len1,len2,len3,len4,len5;
unsigned char msg_id;
unsigned char speed_rx[8],gear_rx[8],temp_rx[8],rpm_rx[8],ind_rx[8];

void main(void) {
    config();
    while(1) {
        can_receive(&len1, &msg_id, gear_rx);
        
        can_receive(&len2, &msg_id, speed_rx);
        
        
        can_receive(&len3, &msg_id, temp_rx);
        

        can_receive(&len4,&msg_id,rpm_rx);

        
        can_receive(&len5,&msg_id,ind_rx);
        
        switch(msg_id) {
            case msg_id_gear: clcd_putch(gear_rx[0], LINE2(0));
                              break;
            case msg_id_speed: clcd_putch(speed_rx[0], LINE2(2));
                               clcd_putch(speed_rx[1], LINE2(3));
                               break;
            case msg_id_temp: clcd_putch(temp_rx[0], LINE2(5));
                              clcd_putch(temp_rx[1], LINE2(6));
                              clcd_putch(temp_rx[2], LINE2(7));
                              clcd_putch(temp_rx[3], LINE2(8));
                              break;  
            case msg_id_rpm: clcd_putch(rpm_rx[0],LINE2(10));
                             clcd_putch(rpm_rx[1],LINE2(11));
                             clcd_putch(rpm_rx[2],LINE2(12));
                             clcd_putch(rpm_rx[3],LINE2(13));
                              break;
            case msg_id_ind: clcd_putch(ind_rx[0],LINE2(15));
                              break;                  
        }
    }
    return;
}
