package uk.lgl.modmenu;

import android.app.Dialog;
import android.content.Intent;
import android.graphics.drawable.ColorDrawable;
import android.os.AsyncTask;
import android.widget.ProgressBar;
import android.widget.Toast;
import eu.chainfire.libsuperuser.Shell;
import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import android.app.AlertDialog;
import android.app.Activity;
import uk.lgl.MainActivity;

public class NepRoot extends Activity {

	// public static native int Init();

	private MainActivity thiz;

	public NepRoot(MainActivity thiz) {
		this.thiz = thiz;
	}

	public void showNoRootMessage() {
		(new AlertDialog.Builder(thiz))
				.setMessage("Could not acquire root")
				.setNegativeButton(android.R.string.ok, null)
				.show();
	}

	public int Game(String pkg) {
		try {
			ArrayList arrayList = new ArrayList();
			Shell.PoolWrapper poolWrapper = Shell.Pool.SU;
			poolWrapper.run("(toolbox ps; toolbox ps -A; toybox ps; toybox ps -A) | grep \" " + pkg + "$\"", arrayList, null, false);
			Iterator iterator = arrayList.iterator();
			while (iterator.hasNext()) {
				String Trim = ((String) iterator.next()).trim();
				while (Trim.contains("  ")) {
					Trim = Trim.replace("  ", " ");
				}
				String[] Split = Trim.split(" ");
				if (Split.length >= 2) {
					return Integer.parseInt(Split[1]);
				}
			}
			return -1;
		} catch (Shell.ShellDiedException e) {
			e.printStackTrace();
			return -1;
		}
	}
}
