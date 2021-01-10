#include "contactFonc.h"

///Fonction callback afin de fermer la fenetre
///Callback fonction to close the window
gboolean on_close (GtkWidget * gwt, gpointer data) {
    gtk_main_quit ();
    return TRUE;
}



///Fonction callback pour delete un contact et décrémenter le nombre de contact stocker
///Callback fonction to delete a contact and decrease the contact count
void Delete_Contact(GtkWidget*gwt, gpointer data) {
    mydata *Udata = data;

    //Permet de vérifier si un contact a été chosie et d'afficher un log à l'utilisateur du programme
    //Verifie if a contact have been choosen and to display a log to the user
    GtkWidget* EditError=(GtkWidget*) gtk_builder_get_object(Udata->build,"Log");
    if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(Udata->combo),&Udata->comboIter)==0){
        gtk_label_set_text(GTK_LABEL(EditError),"you didn't chose a contact to delete in the ComboBox.");
        return;
    }
    gtk_list_store_remove(GTK_LIST_STORE(Udata->listStore),&Udata->comboIter);
    //Décrémentation du nombre de contact
    //Decreasing of the contact count
    Udata->nbr_Contact-=1;
    GtkWidget* Contact_number=(GtkWidget*) gtk_builder_get_object(Udata->build,"nbr_Contact");
    gchar nbr_str[10];
    g_snprintf(nbr_str,10,"%d",Udata->nbr_Contact);
    gtk_label_set_text(GTK_LABEL(Contact_number),nbr_str);
}





///Fonction callback permettant d'éditer le contact choisie dans la combobox
///Callback fonction which enable to edit a choosen contact int the combobox
void Edit_Contact(GtkWidget* btn, gpointer data) {
    mydata *Udata = data;
    Contact eContact;
    GtkWidget* diag_Edit_Contact=(GtkWidget*) gtk_builder_get_object(Udata->build,"Add_Edit_Contact");
    //Get the entrys
    GtkWidget* Lastname=(GtkWidget*) gtk_builder_get_object(Udata->build,"LastName");
    GtkWidget* Firstname=(GtkWidget*) gtk_builder_get_object(Udata->build,"FirstName");
    GtkWidget* Adresse=(GtkWidget*) gtk_builder_get_object(Udata->build,"Adresse");
    GtkWidget* TContact=(GtkWidget*) gtk_builder_get_object(Udata->build,"TContact");
    GtkWidget* Mail=(GtkWidget*) gtk_builder_get_object(Udata->build,"Mail");
    GtkWidget* Num=(GtkWidget*) gtk_builder_get_object(Udata->build,"Num");

    //Vérification de si le contact a été choisie, très important car cela peut provoquer une seg fault
    //Verification if a contact have been choosen, really important because it can produce a seg fault
    GtkWidget* EditError=(GtkWidget*) gtk_builder_get_object(Udata->build,"Log");
    gtk_label_set_text(GTK_LABEL(EditError),"");
    if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(Udata->combo),&Udata->comboIter)==0){
        gtk_label_set_text(GTK_LABEL(EditError),"you didn't chose a contact to edit in the ComboBox.");
        return;
    }
    //Récupération des datas du contact  
    //Recovery of the contact datas
    gtk_tree_model_get(GTK_TREE_MODEL(Udata->listStore),&Udata->comboIter,
    0,&eContact.Nom,1,&eContact.Prenom,2,&eContact.Adresse,3,&eContact.Type_Contact,4,&eContact.email,5,&eContact.Numero,-1);

    //Informations mise dans les entrys
    //Set in the entrys
    gtk_entry_set_text(GTK_ENTRY(Lastname),eContact.Nom);
    gtk_entry_set_text(GTK_ENTRY(Firstname),eContact.Prenom);
    gtk_entry_set_text(GTK_ENTRY(Adresse),eContact.Adresse);
    gtk_entry_set_text(GTK_ENTRY(TContact),eContact.Type_Contact);
    gtk_entry_set_text(GTK_ENTRY(Mail),eContact.email);
    gtk_entry_set_text(GTK_ENTRY(Num),eContact.Numero);

    gtk_widget_show_all(diag_Edit_Contact);

    gint res =gtk_dialog_run(GTK_DIALOG(diag_Edit_Contact));

    //Vérification que les informations essentiel on été garder
    //Verification that the essential informations are still there
    if(gtk_entry_get_text_length(GTK_ENTRY(Lastname)) != 0 && gtk_entry_get_text_length(GTK_ENTRY(Firstname)) != 0 &&
        gtk_entry_get_text_length(GTK_ENTRY(Num)) != 0){
        switch (res)
            {
            case GTK_RESPONSE_ACCEPT:
                //Update des informations du contact avec les infos dans les entrys
                //Updating the contact informations with the one given in the entrys
                eContact.Nom = (gchar*) gtk_entry_get_text(GTK_ENTRY(Lastname));
                eContact.Prenom =(gchar*) gtk_entry_get_text(GTK_ENTRY(Firstname));
                eContact.Adresse =(gchar*) gtk_entry_get_text(GTK_ENTRY(Adresse));
                eContact.Type_Contact =(gchar*) gtk_entry_get_text(GTK_ENTRY(TContact));
                eContact.email =(gchar*) gtk_entry_get_text(GTK_ENTRY(Mail));
                eContact.Numero =(gchar*) gtk_entry_get_text(GTK_ENTRY(Num));
                gtk_list_store_set(GTK_LIST_STORE(Udata->listStore),&Udata->comboIter,
                0, eContact.Nom, 1, eContact.Prenom, 2, eContact.Adresse, 3, eContact.Type_Contact, 4, eContact.email,
                5, eContact.Numero,-1);
                break;
            
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
                break;
            }
        }
    //Gestion d'erreur si des informations essentiel on été enlevé
    //Error handling if the essential infos are removed
    else{
    gtk_label_set_text(GTK_LABEL(EditError),"you removed essential information, Editing refused.");

    }
    //Permet de vider les entry pour la prochaine utilisation vu que on la hide et non destroy/
    //It emptys the entrys since we are not destroying the dialog box but we hide it.
    gtk_entry_set_text(GTK_ENTRY(Lastname),"");
    gtk_entry_set_text(GTK_ENTRY(Firstname),"");
    gtk_entry_set_text(GTK_ENTRY(Adresse),"");
    gtk_entry_set_text(GTK_ENTRY(TContact),"");
    gtk_entry_set_text(GTK_ENTRY(Mail),"");
    gtk_entry_set_text(GTK_ENTRY(Num),"");
    gtk_widget_hide(diag_Edit_Contact);
}





///Display le contact dans une boite de dialogue
///Display a contact inside a dialog box
void Show_Contact(GtkButton *btn,gpointer data) {
    mydata *Udata = data;
    Contact sContact;
    GtkWidget* diag_Affiche_Contact=(GtkWidget*) gtk_builder_get_object(Udata->build,"affiche_contact");
    GtkWidget* Lastname=(GtkWidget*) gtk_builder_get_object(Udata->build,"LastName_tag");
    GtkWidget* Firstname=(GtkWidget*) gtk_builder_get_object(Udata->build,"FirstName_tag");
    GtkWidget* Adresse=(GtkWidget*) gtk_builder_get_object(Udata->build,"Adresse_tag");
    GtkWidget* TContact=(GtkWidget*) gtk_builder_get_object(Udata->build,"TContact_tag");
    GtkWidget* Mail=(GtkWidget*) gtk_builder_get_object(Udata->build,"Mail_tag");
    GtkWidget* Num=(GtkWidget*) gtk_builder_get_object(Udata->build,"Num_tag");

    GtkWidget* EditError=(GtkWidget*) gtk_builder_get_object(Udata->build,"Log");
    gtk_label_set_text(GTK_LABEL(EditError),"");
    if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(Udata->combo),&Udata->comboIter)==0){
        gtk_label_set_text(GTK_LABEL(EditError),"you didn't chose a contact to display in the ComboBox.");
        return;
    }
    gtk_tree_model_get(GTK_TREE_MODEL(Udata->listStore),&Udata->comboIter,
    0,&sContact.Nom,1,&sContact.Prenom,2,&sContact.Adresse,3,&sContact.Type_Contact,4,&sContact.email,5,&sContact.Numero,-1);

    //Set des informations du contact dans les labels
    //Set the informations inside the labels
    gtk_label_set_text(GTK_LABEL(Lastname),sContact.Nom);
    gtk_label_set_text(GTK_LABEL(Firstname),sContact.Prenom);
    gtk_label_set_text(GTK_LABEL(Adresse),sContact.Adresse);
    gtk_label_set_text(GTK_LABEL(TContact),sContact.Type_Contact);
    gtk_label_set_text(GTK_LABEL(Mail),sContact.email);
    gtk_label_set_text(GTK_LABEL(Num),sContact.Numero);
    
    gtk_widget_show_all(diag_Affiche_Contact);

    gint res =gtk_dialog_run(GTK_DIALOG(diag_Affiche_Contact));
    
    switch (res)
    {
    case GTK_RESPONSE_ACCEPT: 
        break;
    
    case GTK_RESPONSE_NONE:
        break;
    }

    gtk_widget_hide(diag_Affiche_Contact);
}






///Ajoute un contact avec ses information à la comboBox
///Add a contact with his informations inside the combobox
void Add_Contact(GtkButton *btn, gpointer data) {
    mydata *Udata = data;
    GtkWidget* diag_Add_Contact=(GtkWidget*) gtk_builder_get_object(Udata->build,"Add_Edit_Contact");

    //Obtention des entrys depuis glade
    //We get the entry from glade
    GtkWidget* Lastname=(GtkWidget*) gtk_builder_get_object(Udata->build,"LastName");
    GtkWidget* Firstname=(GtkWidget*) gtk_builder_get_object(Udata->build,"FirstName");
    GtkWidget* Adresse=(GtkWidget*) gtk_builder_get_object(Udata->build,"Adresse");
    GtkWidget* TContact=(GtkWidget*) gtk_builder_get_object(Udata->build,"TContact");
    GtkWidget* Mail=(GtkWidget*) gtk_builder_get_object(Udata->build,"Mail");
    GtkWidget* Num=(GtkWidget*) gtk_builder_get_object(Udata->build,"Num");

    GtkWidget* EditError=(GtkWidget*) gtk_builder_get_object(Udata->build,"Log");
    gtk_label_set_text(GTK_LABEL(EditError),"");

    Contact LeContact;
    

    gtk_widget_show_all(diag_Add_Contact);

    gint res =gtk_dialog_run(GTK_DIALOG(diag_Add_Contact));
        //Permet de vérifier si il y a assez d'information fournie pour les accepter ou non
        //Enable to verifie if there is enough informations to add the contact
        if(gtk_entry_get_text_length(GTK_ENTRY(Lastname)) != 0 && gtk_entry_get_text_length(GTK_ENTRY(Firstname)) != 0 &&
        gtk_entry_get_text_length(GTK_ENTRY(Num)) != 0){
        
            switch (res)
            {
            case GTK_RESPONSE_ACCEPT:

                LeContact.Nom = (gchar*) gtk_entry_get_text(GTK_ENTRY(Lastname));
                LeContact.Prenom =(gchar*) gtk_entry_get_text(GTK_ENTRY(Firstname));
                LeContact.Adresse =(gchar*) gtk_entry_get_text(GTK_ENTRY(Adresse));
                LeContact.Type_Contact =(gchar*) gtk_entry_get_text(GTK_ENTRY(TContact));
                LeContact.email =(gchar*) gtk_entry_get_text(GTK_ENTRY(Mail));
                LeContact.Numero =(gchar*) gtk_entry_get_text(GTK_ENTRY(Num));

                //Ajout du contact à la liste
                //We add the Contact to the listStore
                gtk_list_store_append(GTK_LIST_STORE(Udata->listStore),&Udata->iter);
                gtk_list_store_set(GTK_LIST_STORE(Udata->listStore),&Udata->iter,
                0, LeContact.Nom, 1, LeContact.Prenom, 2, LeContact.Adresse, 3, LeContact.Type_Contact, 4, LeContact.email,
                5, LeContact.Numero,-1);
                
                Udata->nbr_Contact+=1;
                GtkWidget* Contact_number=(GtkWidget*) gtk_builder_get_object(Udata->build,"nbr_Contact");
                gchar nbr_str[10];
                g_snprintf(nbr_str,10,"%d",Udata->nbr_Contact);
                gtk_label_set_text(GTK_LABEL(Contact_number),nbr_str);
                break;
            
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
                break;
            }
        }
    
    else{
    gtk_label_set_text(GTK_LABEL(EditError),"you didn't give enough information to add your contact.");
    }
    
        //We set "" to remove the content inside the entrys
        gtk_entry_set_text(GTK_ENTRY(Lastname),"");
        gtk_entry_set_text(GTK_ENTRY(Firstname),"");
        gtk_entry_set_text(GTK_ENTRY(Adresse),"");
        gtk_entry_set_text(GTK_ENTRY(TContact),"");
        gtk_entry_set_text(GTK_ENTRY(Mail),"");
        gtk_entry_set_text(GTK_ENTRY(Num),"");
       gtk_widget_hide(diag_Add_Contact);
}