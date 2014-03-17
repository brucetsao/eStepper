#include <PS2X_lib.h>  // 目前是1.6版

PS2X ps2x; // 建立PS2控制器的類別實體

/*
此程式庫不支援熱插拔，亦即，你必須在連接控制器後重新啟動Arduino，
或者在連接控制器之後再次呼叫config_gamepad()函數。
*/
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
 Serial.begin(9600);

 // ********注意！******** 1.6版的新語法：
 // 控制器接腳設置並驗證是否有錯誤:  GamePad(時脈腳位, 命令腳位, 選取腳位, 資料腳位, 是否支援類比按鍵, 是否支援震動) 
 error = ps2x.config_gamepad(13,11,10,12, true, true);
 
 if(error == 0) { // 如果控制器連接沒有問題，就顯示底下的訊息。
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
   Serial.println("holding L1 or R1 will print out the analog stick values.");
   Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1) // 找不到控制器，顯示底下的錯誤訊息。
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)  // 發現控制器，但不接受命令，請參閱程式作者網站的除錯說明。
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3) // 控制器拒絕進入類比感測壓力模式，或許是此控制器不支援的緣故。
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   type = ps2x.readType();  // 偵測控制器器的類型
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");   // 未知的控制器類型
       break;
       case 1:
        Serial.println("DualShock Controller Found");  // 發現DualShock控制器
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");  // 發現吉他英雄控制器
       break;
     }
}

void loop(){
   /* 
   你必須執行ps2x.read_gamepad()方法來獲取新的按鍵值，語法格式：
   ps2x.read_gamepad(小馬達開或關, 大馬達強度值從0~255)
   如果不啟用震動功能，請執行
   ps2x.read_gamepad();
   不需要任何參數。
   
   你應該至少一秒鐘執行一次這個方法。
   */
 if(error == 1) // 如果沒發現任何控制器，則跳出迴圈。
  return; 
  
 if(type == 1) { // 這是標準的DualShock控制器
    ps2x.read_gamepad(false, vibrate);			// 讀取控制器並且命令大的震動馬達以"vibrate"變數值的速度旋轉
    
    if(ps2x.Button(PSB_START))					// 查看「開始」鍵是否被按住
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))				// 查看「選擇」鍵是否被按住
      Serial.println("Select is being held");
         
    if(ps2x.Button(PSB_PAD_UP)) {         // 若「上」按鍵被按著
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   
  
    vibrate = ps2x.Analog(PSAB_BLUE);	// 依據你按著X按鍵的力道來調整馬達的震動強度 

    if (ps2x.NewButtonState())        	// 若「按下」或「放開」任何按鈕
    {
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))    // 若被按下的是三角按鍵
         Serial.println("Triangle pressed"); 
    } 
    
    if(ps2x.ButtonPressed(PSB_RED))             // 若「按下」圈圈按鍵
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK))           // 若「放開」方塊按鍵
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            // 若「按下」或「放開」叉叉按鍵
         Serial.println("X just changed");    
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) //　若按著PSB_L1或PSB_R1按鍵
    {  // 顯示左右類比搖桿的值
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC);
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }   
 }
 delay(50);
}

