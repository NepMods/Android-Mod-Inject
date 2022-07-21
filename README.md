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

![img4](https://pasteboard.co/gD4k4bLyw9fb.png)
