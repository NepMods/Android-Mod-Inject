package uk.lgl.modmenu;


import android.app.Application;
import eu.chainfire.libsuperuser.Shell;
import java.io.IOException;

public class NepCaller extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        try {
            Runtime.getRuntime().exec("su -c");
            Shell.SU.run("setenforce 0");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
