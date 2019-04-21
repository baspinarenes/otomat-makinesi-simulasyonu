#define BUTON25 13
#define BUTON50 14
#define BUTON1 15
#define BUTONsu 31
#define BUTONcay 32
#define BUTONkahve 33
#define BUTONcikolata 34
#define BUTONbiskuvi 35

#define BUTONbitis 37
#define BUTONreset 38

#define kirmiziLed 6
#define yesilLed 7

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

char metin[] = "0,0,1\t1,su,0,50 Kurus\t2,cay,20,1 TL\t3,kahve,15,1.5 TL\t4,cikolata,50,1.75 TL\t5,biskuvi,100,2 TL";

char yazilar[6][50];
String kisimlar[6][4];
float paraUstu;
int bozukParaBilgileri[3];
float kasadakiToplamPara;
float atilanToplamPara;
float alinanlarinParasi;
int atilan25KRS=0, atilan50KRS=0, atilan1TL=0;
int alinanSu=0, alinanCay=0, alinanKahve=0, alinanCikolata=0, alinanBiskuvi=0;
int verilecekler[3];
int stokSu, stokCay, stokKahve, stokCikolata, stokBiskuvi;

void setup()
{

    Serial.begin(9600);
    randomSeed(analogRead(29));
  
    pinMode(BUTON25, INPUT);
    pinMode(BUTON50, INPUT);
    pinMode(BUTON1, INPUT);
    pinMode(BUTONsu, INPUT);
    pinMode(BUTONcay, INPUT);
    pinMode(BUTONkahve, INPUT);
    pinMode(BUTONcikolata, INPUT);
    pinMode(BUTONbiskuvi, INPUT);
    pinMode(BUTONbitis, INPUT);
    pinMode(BUTONreset, INPUT);

    pinMode(kirmiziLed, OUTPUT);
    pinMode(yesilLed, OUTPUT);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enes Baspinar");
    lcd.setCursor(0,1);
    lcd.print("Ertugrul Demir");

    delay(3000);
    lcd.clear();


    KasaBilgisi();
    kasadakiToplamPara = bozukParaBilgileri[0]*0.25 +  bozukParaBilgileri[1]*0.50 +  bozukParaBilgileri[2]*1;

}

void loop()
{

    basaDon:
    Serial.print("Su: ");
    Serial.println(stokSu);
    Serial.print("Cay: ");
    Serial.println(stokCay);
    Serial.print("Kahve: ");
    Serial.println(stokKahve);
    Serial.print("Biskuvi: ");
    Serial.println(stokBiskuvi);
    Serial.print("Cikolata: ");
    Serial.println(stokCikolata);

    Serial.println("-----------------------------------------------------------"); 
    Serial.print("Kasadaki toplam para: "); 
    Serial.println(kasadakiToplamPara);
    Serial.print("Atılan toplam para: "); 
    Serial.println(atilanToplamPara);
    Serial.print("Kasadaki 25 kurus sayisi: "); 
    Serial.println(bozukParaBilgileri[0]);
    Serial.print("Kasadaki 50 kurus sayisi: "); 
    Serial.println(bozukParaBilgileri[1]);
    Serial.print("Kasadaki 1 tl sayisi: "); 
    Serial.println(bozukParaBilgileri[2]);
    Serial.println("-----------------------------------------------------------"); 

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kasadaki para:");
    lcd.setCursor(0,1);
    lcd.print(kasadakiToplamPara);
    lcd.print(" TL");
    
    
    paraAtma(); //atilan toplam parayı elde ettik
    if(atilanToplamPara ==0){
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("sifirlaniyor");
      delay(500); 
      goto basaDon;
    }
      urunSecimi();
      if(atilanToplamPara ==0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("sifirlaniyor"); 
        delay(500); 
        goto basaDon;
      }
      if(atilanToplamPara>=alinanlarinParasi){
        
      }
      else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Atilan para");
        lcd.setCursor(0,1);
        lcd.print("yetersiz.");
        delay(500);
        alinanSu=0, alinanCay=0, alinanKahve=0, alinanCikolata=0, alinanBiskuvi=0;
        atilan25KRS=0, atilan50KRS=0, atilan1TL=0;
        atilanToplamPara = 0;
        goto basaDon;
      }
    
    
    int rastgeleSayi = random(1,5);
    Serial.println("-----------------------------------------------------------"); 
    Serial.print("Rastgele Sayı: "); 
    Serial.println(rastgeleSayi);
    Serial.print("Kasadaki toplam para: "); 
    Serial.println(kasadakiToplamPara);
    Serial.print("Atılan toplam para: "); 
    Serial.println(atilanToplamPara);
    Serial.println("-----------------------------------------------------------"); 
    if(rastgeleSayi==2)
    {
        digitalWrite(kirmiziLed, HIGH);
        delay(3000);
        digitalWrite(kirmiziLed, LOW);
        alinanSu=0, alinanCay=0, alinanKahve=0, alinanCikolata=0, alinanBiskuvi=0;
        atilanToplamPara=0;
        
        atilan25KRS=0, atilan50KRS=0, atilan1TL=0;

        sonResetTusu();
    }
    else
    {
        digitalWrite(yesilLed, HIGH);
        delay(3000);
        digitalWrite(yesilLed, LOW);

        kasadakiToplamPara+=atilanToplamPara;
        bozukParaBilgileri[0] += atilan25KRS;
        bozukParaBilgileri[1] += atilan50KRS;
        bozukParaBilgileri[2] += atilan1TL;
        paraUstu = atilanToplamPara - alinanlarinParasi;

        paraBol(paraUstu, bozukParaBilgileri, verilecekler);

        if(bozukParaBilgileri[0]>verilecekler[0] && bozukParaBilgileri[1]>verilecekler[1] && bozukParaBilgileri[2]>verilecekler[2]){
          lcd.clear();
          lcd.print(paraUstu);
          lcd.print(" TL");
          lcd.setCursor(0,1);
          lcd.print("para ustu odendi");
          delay(3000);
          kasadakiToplamPara -= paraUstu;
          bozukParaBilgileri[0] -= verilecekler[0];
          bozukParaBilgileri[1] -= verilecekler[1];
          bozukParaBilgileri[2] -= verilecekler[2];
          
        }else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Yeterli para");
          lcd.setCursor(0,1);
          lcd.print("ustu yok.");
          delay(1000);
        }
        
        atilanToplamPara=0;
        stokSu-=alinanSu;
        stokCay-=alinanCay;
        stokKahve-=alinanKahve;
        stokBiskuvi-=alinanBiskuvi;
        stokCikolata-=alinanCikolata;
        alinanSu=0, alinanCay=0, alinanKahve=0, alinanCikolata=0, alinanBiskuvi=0;
        atilan25KRS=0, atilan50KRS=0, atilan1TL=0;
    }

    Serial.println("***********************************************************************");
}

void sonResetTusu()
{
    while(1)
    {
        if(digitalRead(BUTONreset)==1)
        {
            
            Serial.print("Para ustu:");
            Serial.println(atilanToplamPara);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Para iadesi");
            lcd.setCursor(0,1);
            lcd.print("yapiliyor.");
            delay(2000);
            break;
            
        }
    }
}

void paraAtma()
{
    boolean birKez = true;
    while(birKez)
    {
        if(digitalRead(BUTON25)==1)
        {
            atilan25KRS++;
            Serial.println("25 KRS");
            delay(300);
            while(1)
            {
                if(digitalRead(BUTON25)==0)
                    break;
            }
        }

        if(digitalRead(BUTON50)==1)
        {
            atilan50KRS++;
            Serial.println("50 KRS");
            delay(300);
            while(1)
            {
                if(digitalRead(BUTON50)==0)
                    break;
            }
        }

        if(digitalRead(BUTON1)==1)
        {
            atilan1TL++;
            Serial.println("1 TL");
            delay(300);
            while(1)
            {
                if(digitalRead(BUTON1)==0)
                    break;
            }
        }

        if(digitalRead(BUTONbitis)==1)
        {

            atilanToplamPara = atilan25KRS*0.25+ atilan50KRS*0.5+ atilan1TL*1;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(atilanToplamPara);
            lcd.print("TL attiniz");
            delay(1000);
            birKez = false;
            while(1)
            {
                if(digitalRead(BUTONbitis)==0)
                    break;
            }
        }

        if(digitalRead(BUTONreset)==1)
        {
            atilanToplamPara = 0;
            atilan1TL=0, atilan25KRS=0, atilan50KRS=0;
            birKez = false;
            while(1)
            { 
                if(digitalRead(BUTONreset)==0)
                    break;
            }
        }
    }
}

void urunSecimi()
{
    boolean birKez = true;
    while(birKez)
    {
        if(digitalRead(BUTONsu)==1)
        {
            if(stokSu ==0 || alinanSu==stokSu)
            {

                Serial.println("Stokta su yok.");
            }
            else
            {
                alinanSu++;
                Serial.println("Su");
            }
            delay(300);
            while(1)
            {
                if(digitalRead(BUTONsu)==0)
                    break;
            }
        }

        if(digitalRead(BUTONcay)==1)
        {
            if(stokCay ==0 || alinanCay==stokCay)
            {

                Serial.println("Stokta cay yok.");
            }
            else
            {
                alinanCay++;
                Serial.println("Cay");
            }

            delay(300);
            while(1)
            {
                if(digitalRead(BUTONcay)==0)
                    break;
            }
        }

        if(digitalRead(BUTONkahve)==1)
        {

            if(stokKahve ==0 || alinanKahve==stokKahve)
            {

                Serial.println("Stokta kahve yok.");
            }
            else
            {
                alinanKahve++;
                Serial.println("Kahve");
            }
            delay(300);
            while(1)
            {
                if(digitalRead(BUTONkahve)==0)
                    break;
            }
        }

        if(digitalRead(BUTONcikolata)==1)
        {
            if(stokCikolata==0 || alinanCikolata==stokCikolata)
            {

                Serial.println("Stokta cikolata yok.");
            }
            else
            {
                alinanCikolata++;
                Serial.println("Cikolata");
            }

            delay(300);

            while(1)
            {
                if(digitalRead(BUTONcikolata)==0)
                    break;
            }
        }

        if(digitalRead(BUTONbiskuvi)==1)
        {
            if(stokBiskuvi==0 || alinanBiskuvi==stokBiskuvi)
            {

                Serial.println("Stokta biskuvi yok.");
            }
            else
            {
                alinanBiskuvi++;
                Serial.println("Biskuvi");
            }

            delay(300);

            while(1)
            {
                if(digitalRead(BUTONbiskuvi)==0)
                    break;
            }
        }

        if(digitalRead(BUTONbitis)==1)
        {
            birKez = false;
            alinanlarinParasi = alinanSu*0.50+alinanCay*1+alinanKahve*1.5+alinanCikolata*1.75+alinanBiskuvi*2;

            while(1)
            {
                if(digitalRead(BUTONbitis)==0)
                    break;
            }
        }

        if(digitalRead(BUTONreset)==1)
        {
            alinanSu=0, alinanCay=0, alinanKahve=0, alinanCikolata=0, alinanBiskuvi=0;
            atilanToplamPara = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("sifirlaniyor");
            delay(300);
            birKez = false;
            while(1)
            {
                if(digitalRead(BUTONreset)==0)
                    break;
            }
        }
    }
}

void KasaBilgisi()
{

    //TEK STRINGDEN SATIRLARI OKUMA
    char ayirac[] = "\t";

    char *ptr = strtok(metin, ayirac);
    int i=0;
    while(ptr != NULL)
    {
        //Serial.println(ptr);

        for(int j = 0; ptr[j] != '\0'; ++j)
        {
            yazilar[i][j] = ptr[j];
        }


        ptr = strtok(NULL, ayirac);
        i++;
    }

    //SATIRLARI KISIMLARA AYIRMA

    char ayirac2[] = ",";
    for(int j=0; j<6; j++)
    {
        ptr = strtok(yazilar[j], ayirac2);
        i=0;

        while(ptr != NULL)
        {
            //Serial.println(ptr);
            char gecic[10] = "";
            for(int f = 0; ptr[f] != '\0'; ++f)
            {


                gecic[strlen(gecic)] = ptr[f];

            }
            //Serial.println(gecic);
            //Serial.println(kisimlar[i]);
            kisimlar[j][i] = gecic;
            ptr = strtok(NULL, ayirac2);
            i++;
        }
    }

    //KASADAKİ PARA BİLGİLERİ

    bozukParaBilgileri[0] = kisimlar[0][0].toInt();
    bozukParaBilgileri[1] = kisimlar[0][1].toInt();
    bozukParaBilgileri[2] = kisimlar[0][2].toInt();

    stokSu = kisimlar[1][2].toInt();
    stokCay = kisimlar[2][2].toInt();
    stokKahve = kisimlar[3][2].toInt();
    stokCikolata = kisimlar[4][2].toInt();
    stokBiskuvi = kisimlar[5][2].toInt();
    /*
    for(int u = 0; u<6; u++){

      Serial.println(kisimlar[u][0]+" "+ kisimlar[u][1] +" "+ kisimlar[u][2]+ " "+ kisimlar[u][3]);

    }*/

}

void paraBol(double a, int kasa[],  int verilecekler[3]){
    verilecekler[2] = floor(a);

    
    double kusurat = a - verilecekler[2];
    
    if(kusurat == 0.75){
        verilecekler[1] = 1;
        verilecekler[0] = 1;
    }
    else if(kusurat == 0.50){
        verilecekler[1] = 1;
        verilecekler[0] = 0;
    }
    else if(kusurat == 0.25){
        verilecekler[1] = 0;
        verilecekler[0] = 1;
    }
    else{
        verilecekler[1] = 0;
        verilecekler[0] = 0;
    }
    
    if(kasa[2]<verilecekler[2]){
        verilecekler[1] += (verilecekler[2]-kasa[2])*2;
        verilecekler[2] = kasa[2];
    }
    if(kasa[1]<verilecekler[1]){
        verilecekler[0] += (verilecekler[1]-kasa[1])*2;
        verilecekler[1] = kasa[1];
    }
    
}
