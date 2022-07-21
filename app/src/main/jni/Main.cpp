#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Menu.h"
#include <SOCKET/client.h>
#include <SOCKET/IncludeClient.h>
ESP espOverlay;

bool feature1, feature2, featureHookToggle, Health;
int sliderValue = 1, level = 0;

enum f {
    f1 = 4,
    f2 = 5,
    f3 = 6,
    f4 = 7,
    f5 = 8,
    f6 = 9,
    f7 = 10,
    f8 = 11,
    f9 = 12,
    f10 = 13,
};


//JNI calls
extern "C" {

    // Do not change or translate the first text unless you know what you are doing
    // Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
    // Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
    // ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
    // Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
    // To learn HTML, go to this page: https://www.w3schools.com/

    JNIEXPORT jobjectArray
    JNICALL
    Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureList(JNIEnv *env, jobject context) {
        jobjectArray ret;

        //Toasts added here so it's harder to remove it
        MakeToast(env, context, OBFUSCATE("Modded by LGL"), Toast::LENGTH_LONG);

        const char *features[] = {
            OBFUSCATE("Category_The Category"),
            //Not counted
            OBFUSCATE("Toggle_The toggle"),
            OBFUSCATE(
                "100_Toggle_True_The toggle 2"),
            //This one have feature number assigned, and switched on by default
            OBFUSCATE("110_Toggle_The toggle 3"),
            //This one too
            OBFUSCATE("SeekBar_The slider_1_100"),
            OBFUSCATE("SeekBar_Kittymemory slider example_1_5"),
            OBFUSCATE("Spinner_The spinner_Items 1,Items 2,Items 3"),
            OBFUSCATE("Button_The button"),
            OBFUSCATE("ButtonLink_The button with link_https://www.youtube.com/"),
            //Not counted
            OBFUSCATE("ButtonOnOff_The On/Off button"),
            OBFUSCATE("CheckBox_The Check Box"),
            OBFUSCATE("InputValue_Input number"),
            OBFUSCATE("InputValue_1000_Input number 2"),
            //Max value
            OBFUSCATE("InputText_Input text"),
            OBFUSCATE("RadioButton_Radio buttons_OFF,Mod 1,Mod 2,Mod 3"),

            //Create new collapse
            OBFUSCATE("Collapse_Collapse 1"),
            OBFUSCATE("CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("123_CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("CollapseAdd_Button_The button"),

            //Create new collapse again
            OBFUSCATE("Collapse_Collapse 2"),
            OBFUSCATE("CollapseAdd_SeekBar_The slider_1_100"),
            OBFUSCATE("CollapseAdd_InputValue_Input number"),

            OBFUSCATE("RichTextView_This is text view, not fully HTML."
                "<b>Bold</b> <i>italic</i> <u>underline</u>"
                "<br />New line <font color='red'>Support colors</font>"
                "<br/><big>bigger Text</big>"),
            OBFUSCATE("RichWebView_<html><head><style>body{color: white;}</style></head><body>"
                "This is WebView, with REAL HTML support!"
                "<div style=\"background-color: darkblue; text-align: center;\">Support CSS</div>"
                "<marquee style=\"color: green; font-weight:bold;\" direction=\"left\" scrollamount=\"5\" behavior=\"scroll\">This is <u>scrollable</u> text</marquee>"
                "</body></html>")
        };

        //Now you dont have to manually update the number everytime;
        int Total_Feature = (sizeof features / sizeof features[0]);
        ret = (jobjectArray)
        env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
            env->NewStringUTF(""));

        for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

        pthread_t ptid;
        pthread_create(&ptid, NULL, antiLeech, NULL);

        return (ret);
    }

    JNIEXPORT void JNICALL
    Java_uk_lgl_modmenu_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
        jint featNum, jstring featName, jint value,
        jboolean boolean, jstring str) {

        LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
            env->GetStringUTFChars(featName, 0), value,
            boolean, str != NULL ? env->GetStringUTFChars(str, 0): "");

        //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

        switch (featNum) {
            case 0:
            feature2 = boolean;
            Send(f::f1, feature2);

            break;
            case 100:
            break;
            case 110:
            break;
            case 1:
            if (value >= 1) {
                sliderValue = value;
            }
            Send(f::f2, sliderValue);
            break;
            case 2:
            Send(f::f3, value);
            case 3:
            Send(f::f4, value);
            case 4:
            Send(f::f5, value);
            // MakeToast(env, obj, OBFUSCATE("Button pressed"), Toast::LENGTH_SHORT);
            break;
            case 5:
            break;
            case 6:
            featureHookToggle = boolean;
            Send(f::f6, featureHookToggle);
            break;
            case 7:
            level = value;
            Send(f::f7, value);
            break;
            case 8:
            //MakeToast(env, obj, TextInput, Toast::LENGTH_SHORT);
            break;
            case 9:
            break;
        }
    }
}
void DrawESP(ESP esp, int screenWidth, int screenHeight) {
    float mScale = (float) screenHeight / (float) 1080;
    esp.DrawText(Color::Yellow(), "Nepmods V1.90", Vector2(screenWidth / 2, screenHeight/1.2), 17);
}


extern "C"
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_DrawOn(JNIEnv *env, jclass type, jobject espView, jobject canvas) {
    espOverlay = ESP(env, espView, canvas);
    if (espOverlay.isValid()) {
        DrawESP(espOverlay, espOverlay.getWidth(), espOverlay.getHeight());
    }
}

extern "C" {
    JNIEXPORT jboolean JNICALL
    Java_uk_lgl_modmenu_FloatingModMenuService_IsConnected(JNIEnv *env, jobject thiz) {
        return client.connected;
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Init(JNIEnv *env, jobject thiz) {
    startClient();
}

extern "C"
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Stop(JNIEnv *env, jobject type) {
    stopClient();
}
