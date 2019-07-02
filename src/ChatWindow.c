#include <gtk/gtk.h>
#include <glib.h>
#include <time.h>
#include "ChatWindow.h"


/*****Global Variables************************/

char recv_m[10000];
int recv_flag = 0;
char username[10000];
int sockfd = 0;

/*********************************************/
void GetUsername(char *u)
{
    strncpy(username, u, strlen(u));
}
void CallChatWindow(char *chatFriend, int sockfd)
{
	DATA *chat_data = g_malloc(sizeof(*chat_data));
	//assert(chat_data);
	chat_data->current_location = 1;
	chat_data->user = 0;
	chat_data->Shutdown = 0;
	chat_data->socket = sockfd;
	chat_data->table = NULL;
	chat_data->main_window = NULL;
    chat_data->Name = chatFriend;
	//g_thread_init(NULL);
	//gdk_threads_init();
	//gtk_init(&argc, &argv);
	/*
	pthread_t receiving;
	pthread_create(&receiving, NULL, Chat_Receive, (void*) chat_data);
	*/
	chat_data->main_window = Chat(chat_data);
	//gdk_threads_enter();
	//gtk_main();	
	
	while((chat_data->Shutdown) == 0){
		Update_Chat();
	}

	/*
	pthread_join(receiving, NULL);
	*/
	//gdk_threads_leave();
	//g_free(chat_data);
	
	close(sockfd);
}



/*********************/


void Send_Message(GtkWidget* button, gpointer g_data )
{
	DATA* data = (DATA*) g_data;
	
	/*
	data->current_location++;
	assert(data->table);
	int sockfd = data->socket;
	gtk_table_resize(GTK_TABLE(data->table), data->current_location, 3);
	const gchar *text = gtk_entry_get_text(GTK_ENTRY(data->chat_entry));
	char send[1000];
	GtkWidget *label = gtk_label_new(text);

	GtkWidget* align_label = gtk_alignment_new(0, 0, 0, 1);
	GtkWidget* align_time = gtk_alignment_new(1, 1, 0, 1);
	gtk_container_add(GTK_CONTAINER(align_label), label);
	gtk_container_add(GTK_CONTAINER(align_time), Time_Stamp());
    gtk_table_attach(GTK_TABLE(data->table), align_label, 0, 1,  data->current_location - 1, data->current_location, GTK_FILL, GTK_SHRINK, 3, 3);
    gtk_widget_show_all(data->table);
	gtk_table_attach(GTK_TABLE(data->table), align_time, 1, 2, data->current_location - 1, data->current_location,  GTK_SHRINK, GTK_SHRINK, 3,  3);

    gtk_widget_show_all(data->table);
	*/
	
    
    
	GdkColor color;
	gdk_color_parse ("dodger blue", &color);
		
		
	GtkTextIter iter;
	int sockfd = data->socket;
	data->current_location++;
	//assert(data->table);
		
	gtk_table_resize(GTK_TABLE(data->table), data->current_location, 2);
		
	GtkWidget *bubble = gtk_text_view_new();
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(bubble));
	const gchar *text = gtk_entry_get_text(GTK_ENTRY(data->chat_entry));
	
	

	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
		

		
/*	gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);
	gtk_text_buffer_create_tag(buffer, "rmarg", "right_margin", 5, NULL);
	gtk_text_buffer_create_tag(buffer, "white_fg", "foreground", "white", NULL); 
	gtk_text_buffer_create_tag(buffer, "bold", "weight", PANGO_WEIGHT_NORMAL, NULL);

*/		
	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, text, -1,  NULL);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(bubble), GTK_WRAP_WORD);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(bubble), FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(bubble), FALSE);
	gtk_widget_modify_base (bubble, GTK_STATE_NORMAL, &color);
	
	/*	
	GtkWidget* align_time = gtk_alignment_new(1, 1, 0, 1);
	gtk_container_add(GTK_CONTAINER(align_time), Time_Stamp());
	
	*/
	GtkWidget* align_label = gtk_alignment_new(1, 0, 1, 0);
	gtk_container_add(GTK_CONTAINER(align_label), bubble);
	
		
		
	gtk_table_attach(GTK_TABLE(data->table), align_label, 1, 2,  data->current_location -1, data->current_location, GTK_FILL, GTK_SHRINK, 3, 3);
	/*
	gtk_table_attach(GTK_TABLE(data->table), align_time, 2, 3, data->current_location - 1, data->current_location, GTK_SHRINK, GTK_SHRINK, 3, 3);
	*/
	gtk_widget_show_all(data->table);
     char send[10000];
    
	/* send string*/
	
    strcpy(send, username);
    strcat(send, ": ");
    strcat(send, text);
    strcat(send, "\n");
	
	/*
	strcpy(send, text);
	*/
    u_int32_t len = htonl(strlen(send));
    write(sockfd, &len, sizeof(len));
	if(write(sockfd, send, strlen(send)) < 0)
    {
		puts("Text could not reach the server.");
        exit(0);
    }
    memset(send,'\0',sizeof(send));
    gtk_entry_set_text(GTK_ENTRY(data->chat_entry), "");
}

void Print_Recieved(DATA* g_data){
	DATA *data = (DATA*) g_data;
	char text[10000];
	//sprintf(text, "%s", data->Name);
    //printf("%s",text);
    //strcpy(text, data->Name);
    //strcat(text, ": ");
    strcpy(text, recv_m);
	strcat(text, "\0");
    strtok(text, "\n");
	if(recv_flag == 1){
    
        /*
        data->current_location++;
        assert(data->table);
        gtk_table_resize(GTK_TABLE(data->table), data->current_location, 3);
        GtkWidget *label = gtk_label_new(text);
        
        GtkWidget* align_label = gtk_alignment_new(0, 0, 0, 1);
        GtkWidget* align_time = gtk_alignment_new(1, 1, 0, 1);
        gtk_container_add(GTK_CONTAINER(align_label), label);
        gtk_container_add(GTK_CONTAINER(align_time), Time_Stamp());
        
        gtk_table_attach(GTK_TABLE(data->table), align_label, 0, 1,  data->current_location - 1, data->current_location, GTK_FILL, GTK_SHRINK, 3, 3);
        gtk_widget_show_all(data->table);
        gtk_table_attach(GTK_TABLE(data->table), align_time, 1, 2, data->current_location - 1, data->current_location,  GTK_SHRINK , GTK_SHRINK, 3,  3);
        
        gtk_widget_show_all(data->table);
        recv_flag = 0;
        */
        
		
		
		GdkColor color;
        if(data->colorflag == 1)
        {
            gdk_color_parse ("medium sea green", &color);
        }
        else
        {
            gdk_color_parse ("light slate gray", &color);

        }
		GtkTextIter iter;
		data->current_location++;
		
		gtk_table_resize(GTK_TABLE(data->table), data->current_location, 2);
		
		GtkWidget *bubble = gtk_text_view_new();
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(bubble));
	
		
		gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
		
/*
		gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);
		gtk_text_buffer_create_tag(buffer, "rmarg", "right_margin", 5, NULL);
		gtk_text_buffer_create_tag(buffer, "white_fg", "foreground", "white", NULL); 
		gtk_text_buffer_create_tag(buffer, "bold", "weight", PANGO_WEIGHT_BOLD, NULL); 

*/
        
		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, text, -1, NULL);
		gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(bubble), GTK_WRAP_WORD);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(bubble), FALSE);
		gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(bubble), FALSE);
		gtk_widget_modify_base (bubble, GTK_STATE_NORMAL, &color);

		/*
		GtkWidget* align_time = gtk_alignment_new(1, 1, 0, 1);
		gtk_container_add(GTK_CONTAINER(align_time), Time_Stamp());
*/
		GtkWidget* align_label = gtk_alignment_new(0, 0, 1, 0);
		gtk_container_add(GTK_CONTAINER(align_label), bubble);
		

		gtk_table_attach(GTK_TABLE(data->table), align_label, 0, 1,  data->current_location -1, data->current_location, GTK_FILL | GTK_EXPAND, GTK_SHRINK, 3, 3);

        
		/*
		gtk_table_attach(GTK_TABLE(data->table), align_time, 2, 3, data->current_location - 1, data->current_location, GTK_SHRINK, GTK_SHRINK, 0, 0);
		*/
		recv_flag = 0;
		gtk_widget_show_all(data->table);
	
	}
	else{
		/**** DO NOTHING***********/
	}
	
}

void Send_Chess(GtkWidget *widget, gpointer g_data){
    DATA *data = (DATA*)g_data;
    char mystring[10000];
    strcpy(mystring, data->Name);
    strcat(mystring, ": ");
    strcat(mystring, "Chess\n");
    write(data->socket, mystring, sizeof(mystring));
   // CallChess(data->socket);
}

GtkWidget *Time_Stamp(void){
	time_t current_time;
	char buffer[32];
	struct tm * time_info;

    current_time = time(NULL);

    time_info = localtime(&current_time);
	
	char timeString[9];  // space for "HH:MM:SS\0"

	strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
	sprintf (buffer, "%s", timeString);
	GtkWidget *label = gtk_label_new(buffer);
	return label;
	
}

GtkWidget* Chat(DATA* orig_data) {
	
  
  	GtkWidget *chatbox;
	GtkWidget *send_button;
	
	
	orig_data->main_window = gtk_dialog_new();
	GtkWidget *window = orig_data->main_window;
	//g_signal_connect(G_OBJECT(orig_data->main_window), "destroy",
    //G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(orig_data->main_window), "delete-event", G_CALLBACK(gtk_main_quit), NULL); 
  	gtk_window_set_title(GTK_WINDOW(window), "Chat");
  	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	
	
	
	GtkWidget *sub_window = gtk_scrolled_window_new(NULL, NULL);
	

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sub_window), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    /*GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(sub_window));
    
    gdouble pagesize = gtk_adjustment_get_page_size(adjustment);
    gdouble upper = gtk_adjustment_get_upper(adjustment);
    gtk_adjustment_set_value(adjustment, upper-pagesize);
    
    gtk_scrolled_window_set_vadjustment(GTK_CONTAINER(sub_window), adjustment);*/
    
    GtkWidget *Frame = gtk_aspect_frame_new(orig_data->Name, .5, .5 ,1.5, FALSE);
	gtk_container_add(GTK_CONTAINER(Frame), sub_window);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(window)->vbox), Frame, TRUE, TRUE, 0);
	gtk_widget_show(sub_window);
	gtk_widget_show(Frame);
	
	

	
	GtkWidget *table;
	table = gtk_table_new (orig_data->current_location, 2, TRUE);
    orig_data->table = table;
	orig_data->current_location++;
    /* set the spacing to 2 on x and 2 on y */
    gtk_table_set_row_spacings (GTK_TABLE (table), 2);
    gtk_table_set_col_spacings (GTK_TABLE (table), 2);
    
    /* pack the table into the scrolled window */
    gtk_scrolled_window_add_with_viewport (
                   GTK_SCROLLED_WINDOW (sub_window), table);
    gtk_widget_show (table);
    
    
    /******TIME TABLE*******/
	/*
	orig_data->time_table = gtk_vbox_new();
	gtk_table_attach(GTK_TABLE (table), name_label, 2, 3, 0, 1, GTK_FILL, GTK_SHRINK, 3, 1);
	gtk_widget_show(orig_data->time_table);
	*/
	/******************************/
    
	
	/*Bottom most Horizontal BOX contents: Same Level as Text Entry Box */
	orig_data->chat_entry = gtk_entry_new();
	GtkWidget *text_entry = orig_data->chat_entry;
	
	send_button = gtk_button_new_with_label("Send");
  	g_signal_connect(GTK_OBJECT (send_button), "clicked",
                        GTK_SIGNAL_FUNC (Send_Message), (gpointer) orig_data);
   g_signal_connect(text_entry, "activate", G_CALLBACK (Send_Message), (gpointer)orig_data);

	GtkWidget* chess_button;
	chess_button = gtk_button_new_with_label("Chess");
	g_signal_connect(GTK_OBJECT (chess_button), "clicked",
                        GTK_SIGNAL_FUNC (Send_Chess), (gpointer) orig_data);
	
	g_thread_create(Chat_Receive, (gpointer) orig_data, FALSE, NULL);
  	chatbox = gtk_hbox_new(FALSE, 1);
	gtk_box_pack_start(GTK_BOX(chatbox),chess_button, FALSE,FALSE, 0);
  	gtk_box_pack_start(GTK_BOX(chatbox), text_entry, TRUE, TRUE, 10);
  	gtk_box_pack_start(GTK_BOX(chatbox), send_button, FALSE, FALSE, 0);
  

	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(window)->action_area), chatbox, TRUE, TRUE,0);
	/************************************************************************************/

	gtk_widget_show_all(window);
	
	
	


	return window;


}

void Update_Chat(void){
	while(gtk_events_pending()){
		gtk_main_iteration();
	}
};

void *Chat_Receive(gpointer g_data)
{
    DATA* data = (DATA*) g_data;
	int sockfd = data->socket;
    char recv[10000];
    bool DontPrintMyMove = false;
    int col_src, row_src, col_dest, row_dest;
    char *boardarray[8][8];
    char move[4];
	for(;;){
		if(data->table == NULL){
		}else{
			if(read(sockfd, recv, sizeof(recv)) > 0)
			{
                if(strncmp(recv, "#STARTW#", sizeof("#STARTW#")) == 0) // initialize board white player
                {
                    BOARD *board = chess();
                    for(int i = 0; i < 8; i++)
                    {
                        for(int j = 0; j < 8; j++)
                        {
                            boardarray[i][j] = board->boardarray[i][j];
                        }
                    }
                    DrawBoard(boardarray);
                    data->colorflag = 1;
                    strcpy(recv, "You have started chess. You are the white player.\n");
                }
                else if(strncmp(recv, "#STARTB#", sizeof("#STARTB#")) == 0) // initialize board white player
                {
                    BOARD *board = chess();
                    for(int i = 0; i < 8; i++)
                    {
                        for(int j = 0; j < 8; j++)
                        {
                            boardarray[i][j] = board->boardarray[i][j];
                        }
                    }
                    DrawBoard(boardarray);
                    data->colorflag = 1;
                    strcpy(recv, "Your friend has started chess. You are the black player.\n");
                }
                else if(strncmp(recv, "#CHESS#", sizeof("#CHESS#")) == 0)
                {
                    read(sockfd, recv, sizeof(recv));
                    unsigned long int separator = strcspn(recv, ":");
                    move[0] = recv[separator+2];
                    move[1] = recv[separator+3];
                    move[2] = recv[separator+4];
                    move[3] = recv[separator+5];
                    col_src = AlphatoNum(move[0]);
                    row_src = (int)(move[1]) - 48;
                    col_dest = AlphatoNum(move[2]);
                    row_dest = (int)(move[3]) - 48;
                    char *temp = boardarray[row_src-1][col_src-1];
                    boardarray[row_dest-1][col_dest-1] = temp;
                    boardarray[row_src-1][col_src-1] = "  ";
                    data->colorflag = 1;
                    DrawBoard(boardarray);
                    if(strlen(username) == separator)
                    {
                        int counter = 0;
                        for(int i = 0; i <separator; i++)
                        {
                            if(recv[i] == username[i])
                            {
                                counter++;
                            }
                        }
                        if(counter == strlen(username))
                        {
                            DontPrintMyMove = true;
                        }
                    }

                }
                if(strncmp(recv, "#START#", sizeof("#START#")) != 0)
                {
                    if(DontPrintMyMove == false)
                    {
                        if(strncmp(recv, "Illegal move. Try again.\n", sizeof("Illegal move. Try again.\n")) == 0)
                        {
                            data->colorflag = 1;
                        }
                        recv[strlen(recv)] = '\0';
                        strcpy(recv_m, recv);
                        recv_flag = 1;
                        gdk_threads_enter();
                        Print_Recieved(data);
                        gdk_threads_leave();
                    }
                }
                DontPrintMyMove = false;
                data->colorflag = 0;
				memset(recv, '\0', sizeof(recv));
			}
		}
	}
    return NULL;
}
