<h1>
  Android Mod Injector
</h1>
<p>
Android Mod Injector Is Mod Menu Injector For Rooted Device & Virtual Device. Made On Lgl Android Mod Menu 2.9. Converted By Nepmods.
  </p>


<H1> How It Works? </h1>
<p> It Have 2 CPP Library, One is Called Client and One Server. basically The server Library is Injected Inside game and All hacks Are controlled By The Client library, Client library is Connected with java, so it is easy to Control Mods.</p>



<H1> How To Use? </h1>
<P>
This Project is Easy To use. but Yu need some experience with modding.
</P>
<H3> Step 1: Targeting Game </h3>
You Need To Target The Game By Entering Game's Package Name On 
<Code>FloatingModMenuServices.java</code>
 And Find <code>targetPackage</code> variable. Then, Replace with Your Game Package.

>If You Change Lib Name in Android.ml, also Change here

![image1](https://i.ibb.co/fX3xWqG/Screenshot-20220721-191944.png)


<H3> Step 2: Targeting Lib </h3>
You need to Target A Library For Hacking Or Making Mod, You can do it on <code>Server.cpp</code>


![img2](https://i.ibb.co/8NXSW43/Screenshot-20220721-192853.png)


<H3>Adding New Feature</h3>
YOU NEED TO ADD NEW FEATURE TO MAKE MODS. 
To do so, <br>
First:
<H4> Creating New Feature</h4>
YOU CAN ADD NEW FEATURE TO <code>Main.cpp</code>file.


![img3](https://i.postimg.cc/0y5TfJqY/Screenshot-20220721-194316.png)

<H4>Creating New Request Id</h4>
You need To Create New Feature Id for Sending / Receiving The Data using Socket.
<Br>For that:

![img4](https://gcdnb.pbrd.co/images/gD4k4bLyw9fb.png?o=1)


<H4>Sending Feature To Server Library</h4>
You can Create A New Case That Matches with Feature position, You can Use <br>
<Code>Send(f::featureID, [bool/int])</code>

![IMG](https://anopic.us/DinoyWOBMqjXANKcQuU0yK6mw61m4E3BfprNveWP.jpg)

<H4>Receiving data</h4>

You can Receive Sent Data In <code>Server.cpp</code>
<Br>
1. Create A New Feature Id With Same Number.
<Br>
2. Receive like showen

```
} else if (request.Mode == f::featureID) {
     feature2 = request.boolean;
     response.Success = true;

```

![img5](https://anopic.us/RcphngTLfeoyH5y4llSBoW7F3sjUcOXavRpgQTEA.jpg)


<H4> Making Mods</h4>
You can Simply Make Mod Like LGL Android Mod Menu 2.9
<Br>

<H1>Change Log</h1>

```
*Change Log*
1. Fixed Injection
2. No Need To Add Libinject Manually, LibInject Will be Added Automatically
3. Changed Root Library From Eu.Chainfire To com.topjohnwu.superuser
4. Fixed For Magisk
5. Fixed For Root
6. Fixed For Virtual Androids
7. made 2 Button To inject
8. Managed Some Codes
```

<H3>Credits</h3>
Making Project: Nepmods (https://GitHub.com/nepmods)<br>
*Inject Lib Framework : Chainfire/evilsocket : https://github.com/Chainfire/inject-hook-cflumen<br>
*Mod Template : LGLTeam : https://github.com/LGLTeam/Android-Mod-Menu<br>
*Socket: Kmods : https://github.com/kp7742<br>
*Help To Inject Fix On Root/Magisk: Mr Any Gamer<br>
