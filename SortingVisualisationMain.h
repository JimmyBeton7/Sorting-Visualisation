/***************************************************************
 * Name:      SortingVisualisationMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2023-07-14
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SORTINGVISUALISATIONMAIN_H
#define SORTINGVISUALISATIONMAIN_H

//(*Headers(SortingVisualisationFrame)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

class SortingVisualisationFrame: public wxFrame
{
    public:

        SortingVisualisationFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SortingVisualisationFrame();

    private:

        //(*Handlers(SortingVisualisationFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void Onexit_btnClick(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(SortingVisualisationFrame)
        static const long ID_BUTTON1;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_SLIDER1;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_PANEL2;
        static const long ID_PANEL1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(SortingVisualisationFrame)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxButton* Button4;
        wxButton* Button5;
        wxButton* exit_btn;
        wxChoice* Choice1;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxSlider* Slider1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxTimer Timer1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SORTINGVISUALISATIONMAIN_H
