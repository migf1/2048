#define GUI_C

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "gui_locale.h"
#include "gui_statusbar.h"
#include "gui_menus.h"
#include "gui.h"

#include "misc.h"
#include "text.h"
#include "gamedata.h"

/* we need this for opening http:// and mailto: links when OS is Windows */
#ifdef G_OS_WIN32
#include <windows.h>
#endif

/* a bit more convenient abstraction of the application's GUI
 *	consists of the smaller structs defined above, along
 *	with a pointer that links the GUI with the core-data.
 */
struct _Gui
{
	gint wmax, hmax;  /* width & height of user's full-screen */

	gboolean  quitOnDestroyAppWindow;
	GuiLocale *locale;
	GtkWidget *appWindow;
	GuiMenus  *menus;

//	GuiSettings   settings;

	struct {
		GtkWidget *ebScoreContainer;  /* event-box parent */
		GtkWidget *score;             /* label child */
		GtkWidget *ebBScoreContainer; /* event-box parent */
		GtkWidget *bscore;            /* label child */
	} scores;

	struct {
		GtkWidget *ebContainer; /* event-box parent of table-widget */
		GtkWidget *table;       /* child of ebContainer */
//		int       dim;          /* single-dimension of the table */
		struct {
			GtkWidget *evbox;                  /* container widget */
			GtkWidget *label;                  /* label widget */
			char       ebname[MAXSIZ_DBGMSG];  /* name of evbox-widget */
			char       lblname[MAXSIZ_DBGMSG]; /* name of label-widget */
			GdkColor   bg;                     /* evbox's bg color */
			GdkColor   fg;                     /* label's fg color */
		} *tiles;
	} board;

	struct {
		GtkWidget *ebContainer; /* event-box parent of toolbar-widget */
		GtkWidget *tb;          /* (toolbar) child of ebContainer */
		GtkWidget *toolPlay;
		GtkWidget *toolPause;
		GtkWidget *toolStop;
		GtkWidget *toolFirst;
		GtkWidget *toolPrev;
		GtkWidget *toolNext;
		GtkWidget *toolLast;
		GtkWidget *toolSlower;
		GtkWidget *toolResetspeed;
		GtkWidget *toolFaster;
	} playback;

	GtkWidget     *imgPrev, *imgNext;

	GtkWidget     *dlgAbout;
	GuiStatusbar  *statusbar;

	Gamedata      *gamedata;
};


GtkWidget *gui_get_appWindow( const Gui *gui );
GuiMenus  *gui_get_menus( const Gui *gui );

/* ---------------------------------------------------
 * Callback function connected to the GTK+ "delete-event"
 * signal, for the main window of the application.
 *
 * When returning FALSE on a "delete-event" signal, GTK+
 * converts it to a "destroy" signal and re-emits it.
 * Returning TRUE means we don't want the window to be
 * destroyed, which may be useful if for example we want
 * to ask for confirmation before destroying the window.
 *
 * Here we just return FALSE, thus telling GTK+ to
 * immediately emit a "destroy" signal.
 * ---------------------------------------------------
 */
static gboolean _on_delete_event_appWindow(
	GtkWidget  *appWindow,
	GdkEvent   *event,
	Gui        *gui
	)
{
	/* avoid compiler warnings for unused parameters */
	if ( NULL == appWindow || NULL == event || NULL == gui ) {
		return FALSE;
	}

	return FALSE;
}

/* ---------------------------------------------------
 * Callback function connected to the "destroy" GTK+ signal,
 * for the main window of the application.
 *
 * The "destroy" signal is emitted by a GTK+ window when
 * the user closes the window, usually by clicking on its
 * close icon (on Windows that's the 'x' icon, located at
 * the top right corner of the window).
 *
 * Normally we just want to terminate the GTK+ main-loop
 * so the flow continues to our cleanup code (if any),
 * in the main() function and then terminate the program.
 *
 * However, in this program a signal for destroying the
 * main application window does not necessarily mean that
 * the user has requested program termination.
 *
 * It could be that the signal has been "artificially"
 * produced by the program itself, when the user requested
 * a dynamic change of the GUI language, right after
 * changing the value of the environment-variable LANG.
 *
 * In those cases, the program schedules the destruction
 * of all its top-level windows (thus its main window too)
 * inside the function: gui_reload_from_glade_file(), by
 * calling gtk_widget_destroy() on all of them.
 *
 * Once this is done, the GUI resources are re-loaded from
 * the Glade file, which means that they get re-initialized
 * according to the new value of LANG, due to GNU-gettext.
 *
 * So obviously, a "destroy" signal sent by the main window
 * of the application does not always dictate program termination.
 *
 * To distinguish whether a "destroy" signal should terminate
 * the main loop of GTK+ or not, I use the boolean variable:
 * gui->quitOnDestroyAppWindow. If it is TRUE gtk_main_quit()
 * is called, otherwise the GTK+ main-loop keeps going on.
 *
 * See also:
 *      gui_reload_gtkGladeFile()
 *	on_activate_miEnglish()
 *	on_activate_miGreek()
 *	on_activate_miEnvironment()
 * ---------------------------------------------------
 */
void on_destroy_appWindow( GtkWidget *appWindow, Gui *gui )
{
	/* avoid compiler warning for unused parameter */
	if ( NULL == appWindow ) {
		gtk_main_quit();
	}

	if ( gui && gui->quitOnDestroyAppWindow ) {
		gtk_main_quit();
	}
}

/* ---------------------------------------------------
 * Callback function connected to the GTK+ "clicked"
 * signal, for the "Reset speed" tool in the playback
 * toolbar.
 *
 * NOTE: When the tool is clicked, we send an "activate"
 *       signal to the menu-item "Play->Speed->Reset",
 *       which corresponds to this tool.
 * ---------------------------------------------------
 */
static void _on_clicked_toolResetspeed( GtkWidget *tool, Gui *gui )
{
	/* avoid compiler warning for unused parameter */
	(void)tool;

	/* sanity checks */
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "Invalid pointer arg (gui)" );
		return;
	}

	GtkWidget *mi = gui_menus_get_mirPlaybackSpeedReset(
				gui_get_menus( gui )
				);
//	g_signal_emit_by_name( mireset, "activate" );
	gtk_menu_item_activate( GTK_MENU_ITEM(mi) );

	return;
}

/* ---------------------------------------------------
 * Callback function connected to the GTK+ "clicked"
 * signal, for the "Slower" tool in the playback toolbar.
 *
 * NOTE: When the tool is clicked, we send an "activate"
 *       signal to the menu-item "Play->Speed->Slower",
 *       which corresponds to this tool.
 * ---------------------------------------------------
 */
static void _on_clicked_toolSlower( GtkWidget *tool, Gui *gui )
{
	/* avoid compiler warning for unused parameter */
	(void)tool;

	/* sanity checks */
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "Invalid pointer arg (gui)" );
		return;
	}

	GtkWidget *mi = gui_menus_get_mirPlaybackSpeedSlower(
				gui_get_menus( gui )
				);
//	g_signal_emit_by_name( mireset, "activate" );
	gtk_menu_item_activate( GTK_MENU_ITEM(mi) );

	return;
}

/* ---------------------------------------------------
 * Callback function connected to the GTK+ "clicked"
 * signal, for the "Faster" tool in the playback toolbar.
 *
 * NOTE: When the tool is clicked, we send an "activate"
 *       signal to the menu-item "Play->Speed->Faster",
 *       which corresponds to this tool.
 * ---------------------------------------------------
 */
static void _on_clicked_toolFaster( GtkWidget *tool, Gui *gui )
{
	/* avoid compiler warning for unused parameter */
	(void)tool;

	/* sanity checks */
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "Invalid pointer arg (gui)" );
		return;
	}

	GtkWidget *mi = gui_menus_get_mirPlaybackSpeedFaster(
				gui_get_menus( gui )
				);
//	g_signal_emit_by_name( mireset, "activate" );
	gtk_menu_item_activate( GTK_MENU_ITEM(mi) );

	return;
}

#ifdef G_OS_WIN32
/* ---------------------------------------------------
 * Callback function connected to the GTK+ "activate-link"
 * signal, for the dialog About.
 *
 * When run on Win32, GTK+ (Gio) cannot open links,
 * thus we overwrite the default behaviour by using
 * our own Win32 specific callback function.
 * ---------------------------------------------------
 */
static gboolean _on_activate_link_dlgAbout(
	GtkWidget  *dlgAbout,
	gchar      *uri,
	Gui        *gui
	)
{
	/* avoid compiler warnings for unused parameters */
	if ( NULL == dlgAbout || NULL == uri ) {
		return FALSE;
	}

	/* sanity checks */
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "Invalid pointer arg (gui)" );
		return FALSE;
	}
	if ( NULL == gui->dlgAbout ) {
		DBG_GUI_ERRMSG( gui->appWindow, "Found invalid GUI elements" );
		return FALSE;
	}

	/* Win32 API call */
	ShellExecute( NULL, "open", uri, NULL, NULL, SW_SHOWNORMAL );

	dbg_print_info( "Signal \"activate-link\" sent for uri: %s\n", uri );


	/* Returning TRUE means we handled the event, so the signal
	* emission should be stopped (don't call any further
	* callbacks that may be connected). Return FALSE
	* to continue invoking callbacks.
	*/
	return TRUE;
}
#endif	/* #ifdef G_OS_WIN32 */

/* ---------------------------------------------------
 * Initialize the main window of the application.
 *
 * Copies the main window widget from the specified GTK+ builder
 * to my GUI abstraction: gui->appWindow, it connects callback
 * functions to it and initializes its visual appearance.
 *
 * NOTE:
 *	The GTK+ callback function: gtk_widget_destroyed()
 *	ensures that the widget pointer will be set to NULL
 *	after the widget gets destroyed.
 * ---------------------------------------------------
 */
static inline gboolean _init_app_window_from_builder(
	Gui        *gui,
	GtkBuilder *builder
	)
{
	if ( NULL == gui->appWindow ) {
		gui->appWindow
		= GTK_WIDGET( gtk_builder_get_object(builder, "windMain") );
	}

	/* ideally we want 800px height, but we need to check user's screen */
//	gtk_widget_set_size_request(gui->appWindow, 800, 600);
	gint h = (gui->hmax < 800) ? gui->hmax : 800;
	gtk_widget_set_size_request( gui->appWindow, 590, h );

	gtk_window_set_icon_from_file(
		GTK_WINDOW( gui->appWindow ),
		FNAME_APPICON,
		NULL
		);
	gtk_window_set_position(
		GTK_WINDOW( gui->appWindow ),
		GTK_WIN_POS_CENTER
		);
	gtk_window_set_title( GTK_WINDOW(gui->appWindow), TXT_APP_NAME );
	gtk_window_set_resizable( GTK_WINDOW(gui->appWindow), FALSE );

	g_signal_connect(
		G_OBJECT( gui->appWindow ),
		"delete-event",
		G_CALLBACK( _on_delete_event_appWindow ),
		gui
		);
	g_signal_connect(
		G_OBJECT( gui->appWindow ),
		"destroy",
		G_CALLBACK( on_destroy_appWindow ),
		gui
		);
	g_signal_connect(
		G_OBJECT( gui->appWindow ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		&gui->appWindow
		);

	return TRUE;
}

/* ---------------------------------------------------
 * Initialize the scores labels.
 *
 * NOTE:
 *	The GTK+ callback function: gtk_widget_destroyed()
 *	ensures that the widget pointer will be set to NULL
 *	after the widget gets destroyed.
 * ---------------------------------------------------
 */
static inline gboolean _init_scores_from_builder(
	Gui        *gui,
	GtkBuilder *builder
	)
{
	char markup[MAXSIZ_DBGMSG] = {'\0'};

	/* just for brevity later on */
	GtkWidget *scoreContainer  = gui->scores.ebScoreContainer;
	GtkWidget *bscoreContainer = gui->scores.ebBScoreContainer;
	GtkWidget *score  = gui->scores.score;
	GtkWidget *bscore = gui->scores.bscore;

	GdkColor bg;    /* for score & bscore event-box containers */
	GdkColor fg;    /* for score & bscore labels */

	gdk_color_parse( "#bbada0", &bg );
	gdk_color_parse( "#eee4da", &fg );

	/* score & bscore containers (event-box widgets) */
	scoreContainer
	= GTK_WIDGET( gtk_builder_get_object(builder, "ebScoreContainer") );

	bscoreContainer
	= GTK_WIDGET( gtk_builder_get_object(builder, "ebBScoreContainer") );

	gtk_widget_modify_bg(
		GTK_WIDGET( scoreContainer ),
		GTK_STATE_NORMAL,
		&bg
		);
	gtk_widget_modify_bg(
		GTK_WIDGET( bscoreContainer ),
		GTK_STATE_NORMAL,
		&bg
		);

	/* score & bscore text (label widgets) */
	score = GTK_WIDGET( gtk_builder_get_object(builder, "lblScore") );
	g_snprintf( markup, MAXSIZ_DBGMSG, TXTF_MARKUP_SCORE, 0L );
	gtk_label_set_markup( GTK_LABEL(score), markup );

	bscore = GTK_WIDGET( gtk_builder_get_object(builder, "lblBScore") );
	g_snprintf( markup, MAXSIZ_DBGMSG, TXTF_MARKUP_BSCORE, 0L );
	gtk_label_set_markup( GTK_LABEL(bscore), markup );

	gtk_widget_modify_fg(
		GTK_WIDGET( score ),
		GTK_STATE_NORMAL,
		&fg
		);
	gtk_widget_modify_fg(
		GTK_WIDGET( bscore ),
		GTK_STATE_NORMAL,
		&fg
		);

	return TRUE;
}

/* ---------------------------------------------------
 *
 * ---------------------------------------------------
 */
static inline void _remove_board_tiles( Gui *gui, int dim )
{
	int i,j, n;

	for (i=0; i < dim; i++) {
		for (j=0; j < dim; j++) {
			n = i * dim + j;

			gtk_widget_destroy( gui->board.tiles[n].evbox );
			memset(&gui->board.tiles[n].ebname,  0, MAXSIZ_DBGMSG);
			memset(&gui->board.tiles[n].lblname, 0, MAXSIZ_DBGMSG);
		}
	}
}

/* ---------------------------------------------------
 *
 * ---------------------------------------------------
 */
static inline gboolean _create_board_tiles( Gui *gui, int dim )
{
	int i,j, n;
	GdkColor fgtile, bgtile;

	gdk_color_parse( "#776e65", &fgtile );
	gdk_color_parse( "#cdc0b4", &bgtile );

	gui->board.tiles = calloc( dim * dim, sizeof( *(gui->board.tiles) ) );
	if ( NULL == gui->board.tiles ) {
		DBG_GUI_ERRMSG( gui->appWindow, "calloc(tiles) failed!" );
		return FALSE;
	}

	for (i=0; i < dim; i++) {
		for (j=0; j < dim; j++) {
			n = i * dim + j;

			gui->board.tiles[n].evbox = gtk_event_box_new();
			g_snprintf(
				gui->board.tiles[n].ebname,
				MAXSIZ_DBGMSG,
				"eb%d%d",
				i,j
				);
			gtk_widget_set_name(
				gui->board.tiles[n].evbox,
				gui->board.tiles[n].ebname
				);

			gui->board.tiles[n].label = gtk_label_new( "" );
			g_snprintf(
				gui->board.tiles[n].lblname,
				MAXSIZ_DBGMSG,
				"lb%d%d",
				i,j
				);
			gtk_widget_set_name(
				gui->board.tiles[n].label,
				gui->board.tiles[n].lblname
				);

			gtk_label_set_markup(
				GTK_LABEL( gui->board.tiles[n].label ),
				"<span font=\"18\" font_weight=\"bold\">0</span>"
				);
			gtk_container_add(
				GTK_CONTAINER( gui->board.tiles[n].evbox ),
				gui->board.tiles[n].label
				);

			gtk_table_attach_defaults( 
				GTK_TABLE( gui->board.table ),
				gui->board.tiles[n].evbox,
				j,    /* left_attach column */
				j+1,  /* right_attach column */
				i,    /* top_attach row */
				i+1   /* bottom_attach row */
				);
			gtk_widget_modify_bg(
				GTK_WIDGET( gui->board.tiles[n].evbox ),
				GTK_STATE_NORMAL,
				&bgtile
				);
			gtk_widget_modify_fg(
				GTK_WIDGET( gui->board.tiles[n].label ),
				GTK_STATE_NORMAL,
				&fgtile
				);
			memcpy(
				&gui->board.tiles[n].bg,
				&bgtile,
				sizeof( GdkColor )
				);
			memcpy(
				&gui->board.tiles[n].fg,
				&fgtile,
				sizeof( GdkColor )
				);
		}
	}

	gtk_widget_show_all( gui->appWindow );
	
	return TRUE;
}

/* ---------------------------------------------------
 * Initialize the board table.
 *
 * NOTE:
 *	The GTK+ callback function: gtk_widget_destroyed()
 *	ensures that the widget pointer will be set to NULL
 *	after the widget gets destroyed.
 * ---------------------------------------------------
 */
static inline gboolean _init_board_from_builder(
	Gui        *gui,
	GtkBuilder *builder
	)
{
	int dim;
	GdkColor bgcontainer;

	gdk_color_parse( "#bbada0", &bgcontainer );

	/* board container (event-box widget) */
	gui->board.ebContainer
	= GTK_WIDGET( gtk_builder_get_object(builder, "ebBoardContainer") );

	gtk_widget_modify_bg(
		GTK_WIDGET( gui->board.ebContainer ),
		GTK_STATE_NORMAL,
		&bgcontainer
		);
	g_signal_connect(
		G_OBJECT( gui->board.ebContainer ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		&gui->board.ebContainer
		);

	/* board table (table-widget) */
	gui->board.table
		= GTK_WIDGET( gtk_builder_get_object(builder, "tableBoard") );
//	gtk_table_resize( GTK_TABLE(gui->board.table), DIM, DIM );
	g_signal_connect(
		G_OBJECT( gui->board.table ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		&gui->board.table
		);
	gtk_table_get_size(
		GTK_TABLE( gui->board.table ),
                (guint *) &dim,
                (guint *) &dim
		);

	/* board tiles */
	if ( !_create_board_tiles(gui, dim) ) {
		DBG_GUI_ERRMSG(
			gui->appWindow,
			"_create_board_tiles() failed!"
			);
		return FALSE;
	}

//	gui->board.dim = dim;
	return TRUE;
}

/* ---------------------------------------------------
 * Initialize the playback toolbar.
 *
 * NOTE:
 *	The GTK+ callback function: gtk_widget_destroyed()
 *	ensures that the widget pointer will be set to NULL
 *	after the widget gets destroyed.
 * ---------------------------------------------------
 */
static inline gboolean _init_tbar_playback_from_builder(
	Gui *gui,
	GtkBuilder *builder
	)
{
	/* just for brevity later on */
	GtkWidget **pw = NULL;        /* pointer to a widget pointer */
	GtkWidget *container = gui->playback.ebContainer;
	GtkWidget *tbar      = gui->playback.tb;

	GdkColor bgcontainer;

	gdk_color_parse( "black", &bgcontainer );

	/* playback-toolbar container (event-box widget) */

	container
	= GTK_WIDGET( gtk_builder_get_object(builder, "ebPlaybackContainer") );

	gtk_widget_modify_bg(
		GTK_WIDGET( container ),
		GTK_STATE_NORMAL,
		&bgcontainer
		);

	/* playback-toolbar */
	tbar = GTK_WIDGET( gtk_builder_get_object(builder, "tbPlayback") );

/*
	gtk_widget_modify_bg(
		GTK_WIDGET( tbar ),
		GTK_STATE_NORMAL,
		&bgcontainer
		);
*/

	/* playback-toolbar tools */

	/* tool: Play */
	pw  = &gui->playback.toolPlay;
	*pw = GTK_WIDGET( gtk_builder_get_object(builder,"toolPlaybackPlay") );
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( on_activate_miPlaybackPlay ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Pause */
	pw  = &gui->playback.toolPause;
	*pw = GTK_WIDGET(gtk_builder_get_object(builder, "toolPlaybackPause"));
	gtk_widget_set_sensitive( *pw, FALSE );
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( on_activate_miPlaybackPause ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Stop */
	pw  = &gui->playback.toolStop;
	*pw = GTK_WIDGET(gtk_builder_get_object(builder, "toolPlaybackStop"));
	gtk_widget_set_sensitive( *pw, FALSE );
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( on_activate_miPlaybackStop ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: First */
	pw  = &gui->playback.toolFirst;
	*pw = GTK_WIDGET(gtk_builder_get_object(builder, "toolPlaybackFirst"));
	gtk_widget_set_sensitive( *pw, FALSE );
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( on_activate_miPlaybackFirst ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Prev */
	pw  = &gui->playback.toolPrev;
	*pw = GTK_WIDGET(gtk_builder_get_object(builder, "toolPlaybackPrev"));
	gtk_widget_set_sensitive( *pw, FALSE );
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( on_activate_miPlaybackPrevious ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Next */
	pw  = &gui->playback.toolNext;
	*pw = GTK_WIDGET(gtk_builder_get_object(builder, "toolPlaybackNext"));
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( on_activate_miPlaybackNext ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Last */
	pw  = &gui->playback.toolLast;
	*pw = GTK_WIDGET(gtk_builder_get_object(builder, "toolPlaybackLast"));
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( on_activate_miPlaybackLast ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Reset speed */
	pw  = &gui->playback.toolResetspeed;
	*pw = GTK_WIDGET(
		gtk_builder_get_object( builder, "toolPlaybackResetspeed" )
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( _on_clicked_toolResetspeed ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Slower speed */
	pw  = &gui->playback.toolSlower;
	*pw = GTK_WIDGET(
		gtk_builder_get_object( builder, "toolPlaybackSlower" )
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( _on_clicked_toolSlower ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* tool: Faster speed */
	pw  = &gui->playback.toolFaster;
	*pw = GTK_WIDGET(
		gtk_builder_get_object( builder, "toolPlaybackFaster" )
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"clicked",
		G_CALLBACK( _on_clicked_toolFaster ),
		gui
		);
	g_signal_connect(
		G_OBJECT( *pw ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		pw
		);

	/* prev & next move indicators */

	gui->imgPrev = GTK_WIDGET( gtk_builder_get_object(builder, "imgPrev") );
	gui->imgNext = GTK_WIDGET( gtk_builder_get_object(builder, "imgNext") );

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file( DIR_GUI"imgNomove.png", NULL );
	gtk_image_set_from_pixbuf( GTK_IMAGE(gui->imgPrev), pixbuf );
	gtk_image_set_from_pixbuf( GTK_IMAGE(gui->imgNext), pixbuf );
	g_object_unref( G_OBJECT(pixbuf) );

	return TRUE;
}

/* ---------------------------------------------------
 * Initialize the "About" dialog.
 *
 * Copies the GUI dialog "About" from the specified GTK+
 * builder into my GUI abstraction: gui->dlgAbout, it
 * initializes the dialog's contents and it connects
 * callback functions.
 *
 * The "About" dialog is defined of type GtkAboutDialog
 * in the Glade file, which provides a standardized way
 * of presenting inormation. However, I haven't found
 * an easy way to access the members of its action-area,
 * namely the buttons: "Credits", "License" and "Close".
 *
 * Consequently, I cannot mark the labels of those buttons
 * as translatable, for the GNU-gettext library (I could
 * implement it as a normal GtkDialog, but I prefer to
 * learn the GtkAboutDialog internals and use them in
 * a future version).
 *
 * NOTE:
 *	The callback function: on_activate_link_dlgAbout()
 *	is connected to the "activate-link" signal ONLY
 *	when the program is compiled under Win32. GTK+'s
 *	file-engine (Gio) has trouble registering the
 *	"http://" and "mailto:" protocols under Win32,
 *	so I conditionally use the Win32 API if needed.
 *
 *	The GTK+ callback function: gtk_widget_destroyed()
 *	ensures that the dialog's pointer will be set to
 *	NULL after the widget gets destroyed.
 * ---------------------------------------------------
 */
static inline gboolean _init_dlg_about_from_builder(
	Gui         *gui,
	GtkBuilder  *builder
	)
{
	GdkPixbuf   *logo      = NULL;
	GError      *error     = NULL;
	const gchar *authors[] = {TXT_APP_AUTHOR, NULL};
	const gchar *artists[] = {TXT_APP_ARTIST, NULL};

	/* load the about-dialog into gui, from the GTK+2 builder */
	gui->dlgAbout = GTK_WIDGET( gtk_builder_get_object(builder, "dlgAbout") );
	g_signal_connect(
		G_OBJECT( gui->dlgAbout ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),
		&gui->dlgAbout
		);

	gtk_window_set_icon_from_file(
		GTK_WINDOW( gui->dlgAbout ),
		FNAME_APPICON,
		NULL
		);

	/* set the about-dialog opacity */
	gtk_window_set_opacity( GTK_WINDOW(gui->dlgAbout), 0.90 );

	/* set the about-dialog logo */
	logo = gdk_pixbuf_new_from_file( FNAME_APPLOGO, &error );
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(gui->dlgAbout), logo );

	/* set the remaining properties */
	gtk_about_dialog_set_program_name(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		gettext( TXT_APP_NAME )
		);

	gtk_about_dialog_set_version(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		gettext( TXT_APP_VERSION )
		);

	gtk_about_dialog_set_comments(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		TXT_APP_DESCRIPTION
		);

	gtk_about_dialog_set_copyright(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		gettext( TXT_APP_COPYRIGHT )
		);

	gtk_about_dialog_set_wrap_license(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		TRUE
		);
	gtk_about_dialog_set_license(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		TXT_APP_LICENSE
		);

	gtk_about_dialog_set_authors(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		authors
		);

	gtk_about_dialog_set_documenters(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		authors
		);

	gtk_about_dialog_set_artists(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		artists
		);

	gtk_about_dialog_set_website_label(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		gettext( TXT_APP_WEBSITE_LABEL )
		);
	gtk_about_dialog_set_website(
		GTK_ABOUT_DIALOG( gui->dlgAbout ),
		TXT_APP_WEBSITE
		);

	/*
	 * connect callback functions to signals emitted by the dialog
	 */

#ifdef G_OS_WIN32
	/* when run on Win32, GTK+ (Gio) cannot open links,
	 * thus we overwrite the default behaviour by using
	 * our own Win32 specific callback function
	 */
	g_signal_connect(
		G_OBJECT(gui->dlgAbout),
		"activate-link",
		G_CALLBACK( _on_activate_link_dlgAbout ),
		gui
		);
#endif

	/* ensure that gui->dlgAbout will be set to NULL after it is destroyed */
	g_signal_connect(
		G_OBJECT( gui->dlgAbout ),
		"destroy",
		G_CALLBACK( gtk_widget_destroyed ),   /* provided by GTK+ */
		&gui->dlgAbout
		);


	return TRUE;
}

/* ---------------------------------------------------
 * Load GUI resources from the specified Glade file.
 *
 * This function uses a GTK+ builder object to read the
 * GUI resources defined in the specified glade-file,
 * then it copies into my GUI abstraction only those
 * resources that need further manipulation dynamically,
 * and it initializes them.
 * ---------------------------------------------------
 */
static inline gboolean _init_from_glade_file( Gui *gui, const gchar *fnameGlade )
{
	GtkBuilder *builder = NULL;
	GError     *error   = NULL;

	/* create a GTK+2 builder with all the widgets defined in the glade-file */
	builder = gtk_builder_new();
	if ( !gtk_builder_add_from_file( builder, fnameGlade, &error ) )
	{
		DBG_GUI_ERRMSG( gui->appWindow, error->message );
		g_warning( "%s: (fatal error) %s", error->message, __func__ );
		g_error_free( error );
		g_object_unref( G_OBJECT(builder) );
		return FALSE;
	}

	/*
	 * TEMPORARILY REMOVE RIGHT PANE:
	 * delete the "vboxWorkareaRight" container & all its children
	 */
	GtkWidget *temp =
		GTK_WIDGET( gtk_builder_get_object(builder, "vboxWorkareaRight") );
	gtk_widget_destroy( temp );

	/* init GUI using only the needed elements from the GTK+2 builder */

	_init_app_window_from_builder( gui, builder );
	gui_menus_init( gui->menus, builder, gui );
	gui_statusbar_init_from_builder( gui->statusbar, builder, gui );
	_init_scores_from_builder( gui, builder );
	_init_board_from_builder( gui, builder );
	_init_tbar_playback_from_builder( gui, builder );
	_init_dlg_about_from_builder( gui, builder );

	/* release the GTK+2 builder */
	g_object_unref( G_OBJECT(builder) );

	return TRUE;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
Gui *gui_free( Gui *gui )
{
	if ( gui ) {
		dbg_gui_locale_print_current(
			gui->locale,
			"___ Local Locale Environment ___"
			);
		dbg_gui_locale_print_inherited(
			gui->locale,
			"___ Will be restored to... ___"
			);

		/* restore os locale environment and free local */
		gui_locale_free( gui->locale );

		/* free menus */
		gui_menus_free( gui->menus );

		/* free statusbar */
		gui_statusbar_free( gui->statusbar );

		/* free board */
		free( gui->board.tiles );
	}
	return NULL;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
Gui *new_gui(
	int      *argc,          /* needed by GTK+ during initialization */
	char     ***argv,         /* needed by GTK+ during initialization */
	Gamedata *gamedata       /* for linking gui to app's core game-data */
	)
{
	Gui       *gui = NULL;
	GdkScreen *fs  = NULL;      /* full-screen */

	/* sanity checks */
	if ( NULL == argc || NULL == argv || NULL == gamedata ) {
		DBG_STDERR_MSG( "(fatal error) NULL pointer argument!" );
		return NULL;
	}

	/* initialize GTK+ */
	if ( !gtk_init_check( argc, argv ) ) {
		DBG_STDERR_MSG( "(fatal error) gtk+ not inited!" );
		return NULL;
	}

	/* instantiate a gui object */
	gui = calloc( 1, sizeof(*gui) );
	if ( NULL == gui ) {
		DBG_STDERR_MSG( "(fatal error) calloc() failed!" );
		return NULL;
	}

	/* link gui with the core game-data of the program */
	gui->gamedata = gamedata;

	/* get & store full-screen dimensions */
	fs = gdk_screen_get_default();
	gui->wmax = gdk_screen_get_width( fs );
	gui->hmax = gdk_screen_get_height( fs );

	/* initiate gui's locale environment */
	gui->locale = new_gui_locale();
	if ( NULL == gui->locale ) {
		DBG_STDERR_MSG( "(fatal error) new_gui_locale() failed!" );
		goto ret_failure;
	}

	/* instantiate gui's menu abstractions */
	gui->menus = new_gui_menus();
	if ( NULL == gui->menus ) {
		DBG_STDERR_MSG( "(fatal error) new_gui_menus() failed!" );
		goto ret_failure;
	}

	/* instantiate gui's statusbar abstraction */
	gui->statusbar = new_gui_statusbar();
	if ( NULL == gui->statusbar ) {
		DBG_STDERR_MSG( "(fatal error) new_gui_statusbar() failed!" );
		goto ret_failure;
	}

	/* initially, destruction of main window results in program-termination */
	gui->quitOnDestroyAppWindow = TRUE;

	/* load resources from Glade file into gui */
	if ( !_init_from_glade_file(gui, FNAME_GLADE) ) {
		DBG_STDERR_MSG( "(fatal error) gui resources not loaded!" );
		goto ret_failure;
	}

	return gui;

ret_failure:
	return gui_free( gui );
}

/* ---------------------------------------------------
 * Reload GUI resources from the specified Glade file.
 *
 * This function is called when the user requests a dynamic
 * change of the GUI language, via the "Language" menu.
 *
 * It schedules the destruction of all the top-level windows
 * of the program by calling gtk_widget_destroy() on them.
 *
 * Before scheduling the main window of the application,
 * it sets 'gui->quitOnDestroyAppWindow' to FALSE so that
 * the connected callback function: on_destroy_appWindow()
 * will NOT terminate the program after destructing the window
 * (remember that 'gui' is passed as user-data to the callback
 * function).
 *
 * Once scheduling is done, 'gui->quitOnDestroyAppWindow'
 * is reset back to TRUE and the GUI resources are loaded
 * from scratch, from the glade-file into my 'gui' abstraction,
 * by calling: gui_load_gtkGladeFile().
 *
 * NOTE:
 *	Before this function is called, the environment-variable
 *	LANG is explicitly set according to the user-request.
 *	Since the GNU-gettext library is runtime-aware with
 *	a LANG dependency, the reloaded GUI is displayed in
 *	the language requested by the user.
 *
 * See also:
 *	on_activate_miEnglish()
 *	on_activate_miGreek()
 *	and on_activate_miEnvironment()
 * ---------------------------------------------------
 */
gboolean gui_reload_from_glade_file( Gui *gui, const gchar *fnameGlade )
{
	/* sanity check */
	if ( NULL == gui || NULL == fnameGlade ) {
		return FALSE;
	}

	/* schedule the destruction of all top-level windows */
	if ( gui->dlgAbout ) {
		gtk_widget_destroy( gui->dlgAbout );
		gui->dlgAbout = NULL;
	}
	if ( gui->appWindow ) {
		gui->quitOnDestroyAppWindow = FALSE;
		gtk_widget_destroy( gui->appWindow );
	}

	gui->quitOnDestroyAppWindow = TRUE;
	return _init_from_glade_file(gui, fnameGlade);
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
gboolean gui_start( Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return FALSE;
	}
	if ( NULL == gui->appWindow ) {
		DBG_GUI_ERRMSG(	NULL, "gui->appWindow is NULL!" );
		return FALSE;
	}

	/* display the main-window of the application, and all its children */
	gtk_widget_show_all( gui->appWindow );

	/* start the GTK+ event loop */
	gtk_main();

	return TRUE;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
GtkWidget *gui_get_appWindow( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return NULL;
	}

	return gui->appWindow;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
GuiLocale *gui_get_locale( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return NULL;
	}

	return gui->locale;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
GuiMenus *gui_get_menus( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return NULL;
	}
	return gui->menus;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
GtkWidget *gui_get_statusbar_widget( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return NULL;
	}
	return gui_statusbar_get_widget( gui->statusbar );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
guint gui_get_statusbar_contextId( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return G_MININT;
	}
	return gui_statusbar_get_contextId( gui->statusbar );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
GtkWidget *gui_get_dlgAbout( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return NULL;
	}
	return gui->dlgAbout;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
Gamedata *gui_get_gamedata( Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return NULL;
	}
	return gui->gamedata;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
char *gui_get_gamedata_fname( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return NULL;
	}
	return gamedata_get_fname( gui->gamedata );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
long int gui_get_gamedata_nmoves( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return 0;
	}
	return gamedata_get_nmoves( gui->gamedata );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
int gui_get_gamedata_dim( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return 0;
	}
	return gamedata_get_dim( gui->gamedata );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
int gui_get_gamedata_sentinel( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return 0;
	}
	return gamedata_get_sentinel( gui->gamedata );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
int gui_get_gamedata_nrandom( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return 0;
	}
	return gamedata_get_nrandom( gui->gamedata );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
unsigned long int gui_get_gamedata_delay( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return 0;
	}
	return gamedata_get_delay( gui->gamedata );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
int gui_get_gamedata_gamewon( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return 0;
	}
	return gamedata_get_gamewon( gui->gamedata );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
gboolean gui_refresh_board( Gui *gui )
{
	guint curdim = 0;
	int   dim = 0;

	/* sanity check */
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG(
			NULL,
			"NULL pointer argument (gui)"
			);
		return FALSE;
	}

	/* demand non-NULL gui->gamedata */
	if ( NULL == gui->gamedata ) {
		DBG_GUI_ERRMSG(
			gui->appWindow,
			"gui->gamedata is NULL!"
			);
		return FALSE;
	}

	/* remove tiles from current board */
	gtk_table_get_size(
		GTK_TABLE(gui->board.table),
		&curdim,
		&curdim
		);
	_remove_board_tiles( gui, (int)curdim );

	/* resize board according to gui->gamedata.dim */
	dim = gamedata_get_dim( gui->gamedata );
	if ( dim < 4 ) {
		DBG_GUI_ERRMSG(
			gui->appWindow,
			"gui->gamedata.dim < 4!"
			);
		return FALSE;
	}

	/* resize board & create tiles */
	gtk_table_resize( GTK_TABLE(gui->board.table), dim, dim );
	if ( !_create_board_tiles(gui, dim) ) {
		DBG_GUI_ERRMSG(
			gui->appWindow,
			"_create_board_tiles() failed!"
			);
		return FALSE;
	}

//	gui->board.dim = dim;

	return TRUE;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
gboolean gui_refresh_statusbar_txtout( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return FALSE;
	}
	return gui_statusbar_refresh_txtout( gui->statusbar, gui );
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
gboolean gui_get_quitOnDestroyAppWindow( const Gui *gui )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)" );
		return FALSE;
	}
	return gui->quitOnDestroyAppWindow;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
gboolean gui_set_quitOnDestroyAppWindow( Gui *gui, gboolean val )
{
	if ( NULL == gui ) {
		DBG_GUI_ERRMSG( NULL, "NULL pointer argument (gui)!" );
		return FALSE;
	}
	gui->quitOnDestroyAppWindow = val;
	return TRUE;
}

/* ---------------------------------------------------
 * 
 * ---------------------------------------------------
 */
gboolean gui_set_gamedata_from_fname( Gui *gui, char *fname )
{
	if ( NULL == gui || NULL == fname ) {
		DBG_GUI_ERRMSG(NULL, "NULL pointer argument (gui or fname)!");
		return FALSE;
	}
	return gamedata_set_from_fname( gui->gamedata, fname );
}
