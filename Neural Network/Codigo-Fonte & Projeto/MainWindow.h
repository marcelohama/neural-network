#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <Math.h>
#include "Rede.h"

// fonte dos dados
Rede rede(0,1,0.1,0.5);

// janela principal e layout
GtkWidget *winWindow;
GtkWidget *tableLayout;
// iteracoes
GtkWidget *iteracaoLabel;
GtkWidget *iteracaoSpinner;
// taxa de aprendizado
GtkWidget *aprendLabel;
GtkWidget *aprendSpinner;
// erro minimo
GtkWidget *erroLabel;
GtkWidget *erroSpinner;
// Neuronios em camada de entrada
GtkWidget *neuronioCamadaEntLabel;
GtkWidget *neuronioCamadaEntView;
// Neuronios em camada interna
GtkWidget *neuronioCamadaIntLabel;
GtkWidget *neuronioCamadaIntSpinner;
// Neuronios em camada de saida
GtkWidget *neuronioCamadaSaiLabel;
GtkWidget *neuronioCamadaSaiView;
// funcao de transferencia
GtkWidget *linearRadio;
GtkWidget *logisticaRadio;
GtkWidget *hiperbolicaRadio;
// vies
GtkWidget *viesCheck;
// arquivo de treino
GtkWidget *arqTreinoLabel;
GtkWidget *treinoButton;
// arquivo de teste
GtkWidget *arqTesteLabel;
GtkWidget *testeButton;
// inicio do treino
GtkWidget *iniciaTreinoButton;
// inicio do teste
GtkWidget *iniciaTesteButton;

class MainWindow {

    public:
        // construtor malévolo da GUI
        MainWindow(int argc, char *argv[]) {
            // inicializa a GUI do GTK
            g_log_set_handler                                   ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
            gtk_init                                            (&argc, &argv);
            g_log_set_handler                                   ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);
            // inicializacao da janela principal e layout
            winWindow = gtk_window_new                          (GTK_WINDOW_TOPLEVEL);
            gtk_window_set_title                                (GTK_WINDOW (winWindow), "Rede Neural Artificial");
            gtk_window_set_position                             (GTK_WINDOW (winWindow), GTK_WIN_POS_CENTER);
            gtk_window_set_resizable                            (GTK_WINDOW (winWindow), FALSE);
            gtk_widget_realize                                  (winWindow);
            g_signal_connect                                    (winWindow, "destroy", gtk_main_quit, NULL);
            tableLayout = gtk_table_new                         (10, 4, FALSE);
            gtk_container_add                                   (GTK_CONTAINER (winWindow), tableLayout);
            // inicializacao dos rotulos
            iteracaoLabel = gtk_label_new                       ("INTERACOES");
            aprendLabel = gtk_label_new                         ("TAXA APR.");
            erroLabel = gtk_label_new                           ("ERRO MAX.");
            neuronioCamadaEntLabel = gtk_label_new              ("  NUM. NEU. ENT.");
            neuronioCamadaIntLabel = gtk_label_new              ("NEU. OCU.");
            neuronioCamadaSaiLabel = gtk_label_new              ("  NUM. NEU. SAI.");
            arqTreinoLabel = gtk_label_new                      ("ARQ. TREINO");
            arqTesteLabel = gtk_label_new                       ("ARQ. TESTES");
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), iteracaoLabel, 0, 1, 0, 1);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), aprendLabel, 0, 1, 1, 2);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), erroLabel, 0, 1, 2, 3);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), neuronioCamadaEntLabel, 0, 1, 4, 5);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), neuronioCamadaIntLabel, 0, 1, 3, 4);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), neuronioCamadaSaiLabel, 0, 1, 5, 6);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), arqTreinoLabel, 3, 5, 0, 1);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), arqTesteLabel, 3, 5, 2, 3);
            // inicializacao dos spinners
            iteracaoSpinner = gtk_spin_button_new               ((GtkAdjustment *)gtk_adjustment_new (1, 1, 10000, 1, 1, 1), 1, 0);
            g_signal_connect                                    (G_OBJECT(iteracaoSpinner), "value-changed", G_CALLBACK(setaIteracao), (gpointer)winWindow);
            aprendSpinner = gtk_spin_button_new                 ((GtkAdjustment *)gtk_adjustment_new (0.1, 0.001, 2, 0.001, 1, 1), 0.01, 3);
            g_signal_connect                                    (G_OBJECT(aprendSpinner), "value-changed", G_CALLBACK(setaAprend), (gpointer)winWindow);
            erroSpinner = gtk_spin_button_new                   ((GtkAdjustment *)gtk_adjustment_new (0.5, 0.001, 3, 0.001, 1, 1), 0.001, 3);
            g_signal_connect                                    (G_OBJECT(erroSpinner), "value-changed", G_CALLBACK(setaErro), (gpointer)winWindow);
            neuronioCamadaEntView = gtk_label_new               ("0");
            neuronioCamadaIntSpinner = gtk_spin_button_new      ((GtkAdjustment *)gtk_adjustment_new (1, 1, 100, 1, 1, 1), 1, 0);
            g_signal_connect                                    (G_OBJECT(neuronioCamadaIntSpinner), "value-changed", G_CALLBACK(setaNeuroInt), (gpointer)winWindow);
            neuronioCamadaSaiView = gtk_label_new               ("0");
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), iteracaoSpinner, 1, 2, 0, 1);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), aprendSpinner, 1, 2, 1, 2);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), erroSpinner, 1, 2, 2, 3);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), neuronioCamadaEntView, 1, 2, 4, 5);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), neuronioCamadaIntSpinner, 1, 2, 3, 4);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), neuronioCamadaSaiView, 1, 2, 5, 6);
            // inicializacao dos radio buttons
            linearRadio = gtk_radio_button_new_with_label       (NULL, "linear");
            g_signal_connect                                    (G_OBJECT(linearRadio), "toggled", G_CALLBACK(setaFuncao), (gpointer)winWindow);
            logisticaRadio = gtk_radio_button_new_with_label    (gtk_radio_button_group (GTK_RADIO_BUTTON (linearRadio)), "logistica");
            g_signal_connect                                    (G_OBJECT(logisticaRadio), "toggled", G_CALLBACK(setaFuncao), (gpointer)winWindow);
            hiperbolicaRadio = gtk_radio_button_new_with_label  (gtk_radio_button_group (GTK_RADIO_BUTTON (linearRadio)), "hiperbolica");
            g_signal_connect                                    (G_OBJECT(hiperbolicaRadio), "toggled", G_CALLBACK(setaFuncao), (gpointer)winWindow);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), linearRadio, 7, 8, 0, 1);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), logisticaRadio, 7, 8, 1, 2);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), hiperbolicaRadio, 7, 8, 2, 3);
            // inicializacao do checkbox do vies
            viesCheck = gtk_check_button_new_with_label         ("Usar Vies");
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), viesCheck, 7, 8, 3, 4);
            g_signal_connect                                    (G_OBJECT(viesCheck), "clicked", G_CALLBACK(setaVies), (gpointer)winWindow);
            // inicializacao do filechooser treino
            treinoButton = gtk_file_chooser_button_new          ("Selecione o arquivo de treino", GTK_FILE_CHOOSER_ACTION_OPEN);
            g_signal_connect                                    (G_OBJECT(treinoButton), "selection_changed", G_CALLBACK(trocaFileNameTreino), (gpointer)winWindow);
            gtk_file_chooser_set_current_folder                 (GTK_FILE_CHOOSER (treinoButton), "C:/");
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), treinoButton, 2, 7, 1, 2);
            // inicializacao do filechooser teste
            testeButton = gtk_file_chooser_button_new           ("Selecione o arquivo de teste", GTK_FILE_CHOOSER_ACTION_OPEN);
            g_signal_connect                                    (G_OBJECT(testeButton), "selection_changed", G_CALLBACK(trocaFileNameTeste), (gpointer)winWindow);
            gtk_file_chooser_set_current_folder                 (GTK_FILE_CHOOSER (testeButton), "C:/");
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), testeButton, 2, 7, 3, 4);

            // inicializacao dos botoes de comando
            iniciaTreinoButton = gtk_button_new_with_label      ("Iniciar Treino");
            g_signal_connect                                    (G_OBJECT (iniciaTreinoButton), "clicked", G_CALLBACK (trainWindow), (gpointer) winWindow);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), iniciaTreinoButton, 2, 8, 4, 5);
            testeButton = gtk_button_new_with_label             ("Testar Rede");
            g_signal_connect                                    (G_OBJECT (testeButton), "clicked", G_CALLBACK (resultWindow), (gpointer) winWindow);
            gtk_table_attach_defaults                           (GTK_TABLE (tableLayout), testeButton, 2, 8, 5, 6);
            // entrada no looping principal
            gtk_widget_show_all                                 (winWindow);
            gtk_main                                            ();
        }

        // janela de exibicao das iteracoes
        static void trainWindow(GtkWidget *wid, GtkWidget *win) {
            // inicializacao da janela
            GtkWidget *dialog = gtk_message_dialog_new          (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_CLOSE, "Pressione [fechar] e aguarde o treino");
            gtk_window_set_position                             (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run                                      (GTK_DIALOG (dialog));
            gtk_widget_destroy                                  (dialog);
            // inicializacao da rede
            rede.reiniciaRede();
            for(unsigned int i=0;i<rede.dadosDeTreino.nAtributos;i++) rede.criaNeuronio(0);
            for(unsigned int i=0;i<rede.dadosDeTreino.nClasses;i++) rede.criaNeuronio(2);
            for(int i=0;i<gtk_spin_button_get_value_as_int((GtkSpinButton*)neuronioCamadaIntSpinner);i++) rede.criaNeuronio(1);
            rede.executaTreino                                  (rede.dadosDeTreino, gtk_spin_button_get_value_as_int((GtkSpinButton*)neuronioCamadaIntSpinner));
        }

        // janela de exibicao dos resultados
        static void resultWindow(GtkWidget *wid, GtkWidget *win) {
            rede.executaTeste(rede.dadosDeTeste, gtk_spin_button_get_value_as_int((GtkSpinButton*)neuronioCamadaIntSpinner), rede.dadosDeTeste.nClasses);
            GtkWidget *dialog = gtk_message_dialog_new          (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Matriz de confusao criada no mesmo diretorio do .exe!");
            gtk_window_set_position                             (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run                                      (GTK_DIALOG (dialog));
            gtk_widget_destroy                                  (dialog);
        }

        // listener do spinner da iteracao
        static void setaIteracao(GtkWidget *wid, GtkWidget *win) {
            //printf("\nIteracoes setadas para %d",gtk_spin_button_get_value_as_int((GtkSpinButton*)iteracaoSpinner));
            rede.iteracoes = gtk_spin_button_get_value_as_int((GtkSpinButton*)iteracaoSpinner);
        }
        // listener do spinner do aprendizado
        static void setaAprend(GtkWidget *wid, GtkWidget *win) {
            //printf("\nAprendizado setado para %.2f",gtk_spin_button_get_value_as_float((GtkSpinButton*)aprendSpinner));
            rede.aprendTaxa = gtk_spin_button_get_value_as_float((GtkSpinButton*)aprendSpinner);
        }
        // listener do spinner do erro minimo
        static void setaErro(GtkWidget *wid, GtkWidget *win) {
            //printf("\nErro minimo setado para %.2f",gtk_spin_button_get_value_as_float((GtkSpinButton*)erroSpinner));
            rede.erroMin = gtk_spin_button_get_value_as_float((GtkSpinButton*)erroSpinner);
        }
        // listener do spinner do numero de neuronios internos
        static void setaNeuroInt(GtkWidget *wid, GtkWidget *win) {
            //printf("\nNeuronios internos setados para %d",gtk_spin_button_get_value_as_int((GtkSpinButton*)neuronioCamadaIntSpinner));
        }

        // listener do radiobox da funcao usada
        static void setaFuncao(GtkFileChooser *ch, GtkWidget *win) {
            if(gtk_toggle_button_get_active((GtkToggleButton*)linearRadio)) {
                //printf("\nfuncao setada para linear");
                rede.funcaoT = 0;
            } else if(gtk_toggle_button_get_active((GtkToggleButton*)logisticaRadio)) {
                //printf("\nfuncao setada para logistica");
                rede.funcaoT = 1;
            }
            else {
                //printf("\nfuncao setada para hiperbolica");
                rede.funcaoT = 2;
            }
        }

        //listener do chebox do vies
        static void setaVies(GtkFileChooser *ch, GtkWidget *win) {
            if(gtk_toggle_button_get_active((GtkToggleButton*)viesCheck)) {
                //printf("\nativando bias");
                rede.vies = true;
            }
            else {
                //printf("\ndesativando bias");
                rede.vies = false;
            }
        }

        // listener do botão de filechooser do arquivo de treino
        static void trocaFileNameTreino(GtkFileChooser *ch, GtkWidget *win) {
            gchar *file = gtk_file_chooser_get_filename         (GTK_FILE_CHOOSER(ch));
            char buff[10];
            int valor;
            double sem_funcao;
            // inicializacao da matriz de dados
            rede.dadosDeTreino = Matriz();
            rede.dadosDeTreino.loadFile                         (file);
            rede.dadosDeTreino.showTuplas();
            // atribuicao dos labels de informacao a respeito do numero de neuronios usados
            sprintf                                             (buff,"%d",rede.dadosDeTreino.nAtributos);
            gtk_label_set_text                                  ((GtkLabel*)neuronioCamadaEntView,buff);
            sprintf                                             (buff,"%d",rede.dadosDeTreino.nClasses);
            gtk_label_set_text                                  ((GtkLabel*)neuronioCamadaSaiView,buff);

            if(modf(sqrt(rede.dadosDeTreino.nClasses*rede.dadosDeTreino.nAtributos),&sem_funcao) > 5)
                valor = (int)ceil(sqrt(rede.dadosDeTreino.nClasses*rede.dadosDeTreino.nAtributos));
            else
                valor = (int)floor(sqrt(rede.dadosDeTreino.nClasses*rede.dadosDeTreino.nAtributos));
            gtk_spin_button_set_value                           ((GtkSpinButton*)neuronioCamadaIntSpinner,valor);
        }

        // listener do botão de filechooser do arquivo de teste
        static void trocaFileNameTeste(GtkFileChooser *ch, GtkLabel *lb) {
            gchar *file = gtk_file_chooser_get_filename         (GTK_FILE_CHOOSER(ch));
            rede.dadosDeTeste = Matriz();
            rede.dadosDeTeste.loadFile                          (file);
            rede.dadosDeTeste.showTuplas();
        }

};

#endif
