/***************************************************************
 * Name:      SortingVisualisationMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2023-07-14
 * Copyright:  ()
 * License:
 **************************************************************/

#include "SortingVisualisationMain.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h> // Dodaj ten nag³ówek dla wxClientDC
#include <wx/pen.h>
#include <algorithm>
#include <random>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <cmath>
using namespace std;
//(*InternalHeaders(SortingVisualisationFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SortingVisualisationFrame)
const long SortingVisualisationFrame::ID_BUTTON1 = wxNewId();
const long SortingVisualisationFrame::ID_CHOICE1 = wxNewId();
const long SortingVisualisationFrame::ID_STATICTEXT1 = wxNewId();
const long SortingVisualisationFrame::ID_BUTTON2 = wxNewId();
const long SortingVisualisationFrame::ID_BUTTON3 = wxNewId();
const long SortingVisualisationFrame::ID_SLIDER1 = wxNewId();
const long SortingVisualisationFrame::ID_BUTTON4 = wxNewId();
const long SortingVisualisationFrame::ID_STATICTEXT2 = wxNewId();
const long SortingVisualisationFrame::ID_BUTTON5 = wxNewId();
const long SortingVisualisationFrame::ID_BUTTON6 = wxNewId();
const long SortingVisualisationFrame::ID_PANEL2 = wxNewId();
const long SortingVisualisationFrame::ID_PANEL1 = wxNewId();
const long SortingVisualisationFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SortingVisualisationFrame,wxFrame)
    //(*EventTable(SortingVisualisationFrame)
    //*)
END_EVENT_TABLE()

SortingVisualisationFrame::SortingVisualisationFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SortingVisualisationFrame)
    Create(parent, id, _("Sorting Visualisation"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1365,700));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(448,296), wxSize(1365,584), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel2 = new wxPanel(Panel1, ID_PANEL2, wxPoint(16,16), wxSize(1336,56), wxBORDER_DOUBLE|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    exit_btn = new wxButton(Panel2, ID_BUTTON1, _("Exit"), wxPoint(1240,8), wxSize(87,40), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Choice1 = new wxChoice(Panel2, ID_CHOICE1, wxPoint(224,16), wxSize(175,39), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->Append(_("Bubblesort"));
    Choice1->Append(_("Quicksort"));
    Choice1->Append(_("Selectionsort"));
    Choice1->Append(_("Insertionsort"));
    Choice1->Append(_("Cocktailsort"));
    Choice1->Append(_("Shellsort"));
    Choice1->Append(_("Bingosort"));
    Choice1->Append(_("Cyclesort"));
    Choice1->Append(_("Combsort"));
    Choice1->Append(_("Pancakesort"));
    wxFont Choice1Font(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    Choice1->SetFont(Choice1Font);
    StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Choose sorting algorithm:"), wxPoint(16,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(11,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    Button1 = new wxButton(Panel2, ID_BUTTON2, _("Generate"), wxPoint(856,8), wxSize(98,40), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button2 = new wxButton(Panel2, ID_BUTTON3, _("Mix"), wxPoint(960,8), wxSize(90,40), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Slider1 = new wxSlider(Panel2, ID_SLIDER1, 100, 10, 1000, wxPoint(560,16), wxSize(174,28), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    Slider1->SetTickFreq(10);
    Button3 = new wxButton(Panel2, ID_BUTTON4, _("Start"), wxPoint(1056,8), wxSize(88,40), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button3->Disable();
    StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("Animation speed:"), wxPoint(416,24), wxSize(144,22), 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(11,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    Button4 = new wxButton(Panel2, ID_BUTTON5, _("Stop"), wxPoint(1152,8), wxSize(85,40), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Button4->Disable();
    Button5 = new wxButton(Panel2, ID_BUTTON6, _("Reset"), wxPoint(760,8), wxSize(93,40), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    Button5->Disable();
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(100, false);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingVisualisationFrame::Onexit_btnClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingVisualisationFrame::OnButton1Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingVisualisationFrame::OnButton2Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingVisualisationFrame::OnButton3Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingVisualisationFrame::OnButton4Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingVisualisationFrame::OnButton5Click);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&SortingVisualisationFrame::OnTimer1Trigger);
    //*)
}

SortingVisualisationFrame::~SortingVisualisationFrame()
{
    //(*Destroy(SortingVisualisationFrame)
    //*)
}
//------------------------------------------------------
//GLOBAL VARIABLES:

wxVector<int>heights;
bool stop_thread = false;

//------------------------------------------------------

void DrawRectangles(wxPanel* panel, int idx, int idx2)
{
    wxClientDC dc(panel);
    dc.Clear();

    // Pobierz rozmiary panelu
    int panelWidth, panelHeight;
    panel->GetSize(&panelWidth, &panelHeight);

    // Oblicz rozmiary i polozenie prostokatow
    int rectWidth = 20;
    int rectHeight;
    int rectSpacing = 2;
    int rectX = panelWidth - (panelWidth - 30);
    int rectY = panelHeight - 10;

    dc.SetPen(wxPen(wxColour(255, 0, 0), 1)); // Czerwony kolor, grubosc linii 2 piksele

    for (int i = 1; i <= 50; i++)
    {
        if(i == idx)
        {
            dc.SetBrush(wxBrush(wxColour(0, 255, 0), wxBRUSHSTYLE_SOLID));
        }
        else if(i == idx2)
        {
            dc.SetBrush(wxBrush(wxColour(255, 0, 0), wxBRUSHSTYLE_SOLID));
        }
        else
        {
            dc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_SOLID));
        }
        rectHeight = heights[i-1];
        dc.DrawRectangle(rectX, rectY, rectWidth, rectHeight);
        rectX += rectWidth+ rectSpacing;
    }
}

void BubbleSort(wxPanel* panel)
{
    wxClientDC dc(panel);
    const int n = 50;
    for(int i = 1; i < n; i++)
    {
        for(int j = n - 1; j >= 1; j--)
        {
            if(heights[j] < heights[j-1])
            {
                int temp = heights[j-1];
                heights[j-1] = heights[j];
                heights[j] = temp;
                //DrawRectangles(panel);
            }
        }
    }
}

void QuickSort(wxPanel *panel, int left, int right, wxSlider *slider)
{
        int temp;
        int pivot = heights[0];
        int p = left;
        int q = right;
        do
        {
            while(heights[q] > pivot) q--; // x
            while(heights[p] < pivot) p++; // x
            if(p <= q)
            {
                temp = heights[p];
                heights[p] = heights[q];
                heights[q] = temp;
                p++;
                q--;
            }
        }while(p <= q);

        if(q > left) QuickSort(panel,left,q,slider);
        if(p < right) QuickSort(panel,p,right,slider);
}

void SortingVisualisationFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SortingVisualisationFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void SortingVisualisationFrame::Onexit_btnClick(wxCommandEvent& event)
{
    Close(true);
}

void SortingVisualisationFrame::OnButton1Click(wxCommandEvent& event)
{
    Button1->Enable(false);
    wxClientDC dc(Panel1);

    // Pobierz rozmiary panelu
    int panelWidth, panelHeight;
    Panel1->GetSize(&panelWidth, &panelHeight);

    // Oblicz rozmiary i polozenie prostokatów
    int rectWidth = 20;
    int rectHeight = -500; //-10
    int rectSpacing = 2;
    int rectX = panelWidth - (panelWidth - 30);
    int rectY = panelHeight - 10;

    // Ustaw kolor i styl rysowania
    dc.SetPen(wxPen(wxColour(255, 0, 0), 1)); // Czerwony kolor, grubosc linii 2 piksele

    // Narysuj prostokaty obok siebie
    for (int i = 1; i <= 50; i++)
    {
        dc.DrawRectangle(rectX, rectY, rectWidth, rectHeight);
        heights.push_back(rectHeight);
        rectX += rectWidth+ rectSpacing;
        rectHeight += 10;
    }
}

void SortingVisualisationFrame::OnButton2Click(wxCommandEvent& event)
{
    //MIX BUTTON
    Button3->Enable(true);

    std::random_device rd;
    std::mt19937 generator(rd());

    shuffle(heights.begin(),heights.end(),generator);
    wxClientDC dc(Panel1);
    dc.Clear();

    // Pobierz rozmiary panelu
    int panelWidth, panelHeight;
    Panel1->GetSize(&panelWidth, &panelHeight);

    // Oblicz rozmiary i polozenie prostokatów
    int rectWidth = 20;
    int rectHeight;
    int rectSpacing = 2;
    int rectX = panelWidth - (panelWidth - 30);
    int rectY = panelHeight - 10;

    dc.SetPen(wxPen(wxColour(255, 0, 0), 1)); // Czerwony kolor, grubosc linii 2 piksele

    for (int i = 1; i <= 50; i++)
    {
        rectHeight = heights[i-1];
        dc.DrawRectangle(rectX, rectY, rectWidth, rectHeight);
        rectX += rectWidth+ rectSpacing;
    }
}

void SortingVisualisationFrame::OnTimer1Trigger(wxTimerEvent& event)
{

}

int getNextGap(int gap) //COMBSORT
{
    gap = (gap*10)/13;
    if (gap < 1)
    {
        return 1;
    }
    return gap;
}

int findMax(wxVector<int>arr, int n) //PANCAKESORT
{
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
    {
        if (arr[i] > arr[mi])
        {
            mi = i;
        }
    }
    return mi;
}

void SortingVisualisationFrame::OnButton3Click(wxCommandEvent& event)
{
    //START BUTTON
    stop_thread = false;
    Button3->Enable(false);
    Button3->SetLabel("Start");
    Button5->Enable(false);
    Button2->Enable(false);
    Button4->Enable(true);

    wxString selectedOption = Choice1->GetString(Choice1->GetSelection());

    enum Options {Option1, Option2, Option3, Option4, Option5, Option6, Option7, Option8, Option9, Option10};
    Options selectedValue;

    if (selectedOption == "Bubblesort")
    {
        selectedValue = Option1;
    }
    else if (selectedOption == "Quicksort")
    {
        selectedValue = Option2;
    }
    else if (selectedOption == "Selectionsort")
    {
        selectedValue = Option3;
    }
    else if (selectedOption == "Insertionsort")
    {
        selectedValue = Option4;
    }
    else if (selectedOption == "Cocktailsort")
    {
        selectedValue = Option5;
    }
    else if (selectedOption == "Shellsort")
    {
        selectedValue = Option6;
    }
    else if (selectedOption == "Bingosort")
    {
        selectedValue = Option7;
    }
    else if (selectedOption == "Cyclesort")
    {
        selectedValue = Option8;
    }
    else if (selectedOption == "Combsort")
    {
        selectedValue = Option9;
    }
    else if (selectedOption == "Pancakesort")
    {
        selectedValue = Option10;
    }

    switch(selectedValue)
    {
        case Option1: //BUBBLESORT
        {
            thread t1([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                const int n = 50;
                for(int i = 1; i < n; i++)
                {
                    for(int j = n - 1; j >= 1; j--)
                    {
                        if(heights[j] < heights[j-1])
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            int temp = heights[j-1];
                            int index = j;
                            heights[j-1] = heights[j];
                            heights[j] = temp;
                            lock.lock();
                            DrawRectangles(Panel1,index,-1);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                        }
                    }
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t1.detach();
            break;
        }

        case Option2: //QUICKSORT
        {
            thread t2([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                QuickSort(Panel1,heights[0],heights.back(),Slider1);
                lock.lock();
                DrawRectangles(Panel1,-1,-1);
                lock.unlock();
                int sleeptime = Slider1->GetValue();
                this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                //-----------------------------------------
            });
            t2.detach();
            break;
        }

        case Option3: //SELECTIONSORT
        {
            thread t2([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                int min_idx;
                for (int i = 0; i < heights.size() - 1; i++)
                {
                    min_idx = i;
                    for (int j = i + 1; j < heights.size(); j++)
                    {
                        if (heights[j] < heights[min_idx])
                        min_idx = j;
                    }
                    if (min_idx != i)
                    {
                        if(stop_thread == true)
                        {
                            return;
                        }
                        int temp = heights[min_idx];
                        heights[min_idx] = heights[i];
                        heights[i] = temp;
                        int index = i;
                        int index2 = min_idx;
                        lock.lock();
                        DrawRectangles(Panel1,index,index2);
                        lock.unlock();
                        int sleeptime = Slider1->GetValue();
                        this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                    }
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t2.detach();
            break;
        }
        case Option4: //INSERTIONSORT
        {
            thread t3([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                int key, j;
                for (int i = 1; i < heights.size(); i++)
                {
                    key = heights[i];
                    j = i - 1;
                    while (j >= 0 && heights[j] > key)
                    {
                        if(stop_thread == true)
                        {
                            return;
                        }
                        heights[j + 1] = heights[j];
                        int index = j+1;
                        int index2 = j;
                        lock.lock();
                        DrawRectangles(Panel1,index,index2);
                        lock.unlock();
                        int sleeptime = Slider1->GetValue();
                        this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                        j = j - 1;
                    }
                    heights[j + 1] = key;
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t3.detach();
            break;
        }
        case Option5: //COCKTAILSORT
        {
            thread t4([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                bool swapped = true;
                int start = 0;
                int end = heights.size() - 1;

                while (swapped)
                {
                    swapped = false;
                    for (int i = start; i < end; ++i)
                    {
                        if (heights[i] > heights[i + 1])
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            int temp = heights[i];
                            heights[i] = heights[i + 1];
                            heights[i + 1] = temp;
                            int index = i;
                            int index2 = i + 1;
                            lock.lock();
                            DrawRectangles(Panel1,index,index2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                            swapped = true;
                        }
                    }

                    if (!swapped)
                    {
                        break;
                    }

                    swapped = false;
                    --end;

                    for (int i = end - 1; i >= start; --i)
                    {
                        if (heights[i] > heights[i + 1])
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            int temp = heights[i];
                            heights[i] = heights[i + 1];
                            heights[i + 1] = temp;
                            int index = i;
                            int index2 = i + 1;
                            lock.lock();
                            DrawRectangles(Panel1,index,index2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                            swapped = true;
                        }
                    }
                    ++start;
                }
            //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t4.detach();
            break;
        }
        case Option6: //SHELLSORT
        {
            thread t5([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                for (int gap = heights.size()/2; gap > 0; gap /= 2)
                {
                    for (int i = gap; i < heights.size(); i += 1)
                    {
                        int temp = heights[i];
                        int j;
                        for (j = i; j >= gap && heights[j - gap] > temp; j -= gap)
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            heights[j] = heights[j - gap];
                            lock.lock();
                            int in = j;
                            int in2 = j - gap;
                            DrawRectangles(Panel1,in,in2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                        }
                        if(stop_thread == true)
                        {
                            return;
                        }
                        heights[j] = temp;
                        int index = j;
                        lock.lock();
                        DrawRectangles(Panel1,index,-1);
                        lock.unlock();
                        int sleeptime = Slider1->GetValue();
                        this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                    }
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t5.detach();
            break;
        }
        case Option7: //BINGOSORT
        {
            thread t6([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                int min = -500;
                int max = -10;
                //-----------------------------------------
                int bingo = min; //heights[0]
                int nextBingo = heights[0];
                int largestEle = max;
                int nextElePos = 0;
                while (bingo < nextBingo)
                {
                    int startPos = nextElePos;
                    for (int i = startPos; i < heights.size(); i++)
                    {
                        if (heights[i] == bingo)
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            int temp = heights[i];
                            heights[i] = heights[nextElePos];
                            heights[nextElePos] = temp;
                            nextElePos = nextElePos + 1;
                            int index = i;
                            int index2 = nextElePos;
                            lock.lock();
                            DrawRectangles(Panel1,index,index2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                        }
                        else if (heights[i] < nextBingo)
                        {
                            nextBingo = heights[i];
                        }
                    }
                    bingo = nextBingo;
                    nextBingo = largestEle;
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t6.detach();
            break;
        }
        case Option8: //CYCLESORT
        {
            thread t7([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                int writes = 0;

                for (int cycle_start = 0; cycle_start <= heights.size() - 2; cycle_start++)
                {
                    int item = heights[cycle_start];
                    int pos = cycle_start;
                    for (int i = cycle_start + 1; i < heights.size(); i++)
                    {
                        if (heights[i] < item)
                        {
                            pos++;
                        }
                    }
                    if (pos == cycle_start)
                    {
                        continue;
                    }
                    while (item == heights[pos])
                    {
                        pos += 1;
                    }
                    if (pos != cycle_start)
                    {
                        int temp = item;
                        item = heights[pos];
                        heights[pos] = temp;
                        int index = pos;
                        int index2;
                        for(int a = 0; a < heights.size(); a++)
                        {
                            if(heights[a] == item)
                            {
                                index2 = a;
                                break;
                            }
                        }
                        if(stop_thread == true)
                        {
                            return;
                        }
                        lock.lock();
                        DrawRectangles(Panel1,index,index2);
                        lock.unlock();
                        int sleeptime = Slider1->GetValue();
                        this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                        writes++;
                    }
                    while (pos != cycle_start)
                    {
                        pos = cycle_start;
                        for (int i = cycle_start + 1; i < heights.size(); i++)
                        {
                            if (heights[i] < item)
                            {
                                pos += 1;
                            }
                        }
                        while (item == heights[pos])
                        {
                            pos += 1;
                        }
                        if (item != heights[pos])
                        {
                            int temp = item;
                            item = heights[pos];
                            heights[pos] = temp;
                            int index = pos;
                            int index2;
                            for(int a = 0; a < heights.size(); a++)
                            {
                                if(heights[a] == item)
                                {
                                    index2 = a;
                                    break;
                                }
                            }
                            if(stop_thread == true)
                            {
                                return;
                            }
                            lock.lock();
                            DrawRectangles(Panel1,index,index2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                            writes++;
                        }
                    }
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t7.detach();
            break;
        }
        case Option9: //COMBSORT
        {
            thread t8([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                int gap = heights.size();
                bool swapped = true;
                while (gap != 1 || swapped == true)
                {
                    gap = getNextGap(gap);
                    swapped = false;
                    for (int i=0; i<heights.size()-gap; i++)
                    {
                        if (heights[i] > heights[i+gap])
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            int temp = heights[i];
                            heights[i] = heights[i+gap];
                            heights[i+gap] = temp;
                            int index = i;
                            int index2 = i+gap;
                            lock.lock();
                            DrawRectangles(Panel1,index,index2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                            swapped = true;
                        }
                    }
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t8.detach();
            break;
        }
        case Option10: //PANCAKESORT
        {
            thread t9([&]()
            {
                mutex dcMutex;
                unique_lock<mutex> lock(dcMutex, defer_lock);
                //-----------------------------------------
                for (int curr_size = heights.size(); curr_size > 1; --curr_size)
                {
                    int mi = findMax(heights, curr_size);
                    if (mi != curr_size - 1)
                    {
                        //flip(arr, mi);
                        int temp, start = 0;
                        while (start < mi)
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            temp = heights[start];
                            heights[start] = heights[mi];
                            heights[mi] = temp;
                            int index = start;
                            int index2 = mi;
                            lock.lock();
                            DrawRectangles(Panel1,index,index2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                            start++;
                            mi--;
                        }
                        start = 0;
                        //flip(arr, curr_size - 1);
                        int x = curr_size - 1;
                        while (start < x)
                        {
                            if(stop_thread == true)
                            {
                                return;
                            }
                            temp = heights[start];
                            heights[start] = heights[x];
                            heights[x] = temp;
                            int index = start;
                            int index2 = x;
                            lock.lock();
                            DrawRectangles(Panel1,index,index2);
                            lock.unlock();
                            int sleeptime = Slider1->GetValue();
                            this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
                            start++;
                            x--;
                        }
                    }
                }
                //-----------------------------------------
                DrawRectangles(Panel1,-1,-1);
            });
            t9.detach();

            break;
        }
    }

}

void SortingVisualisationFrame::OnButton4Click(wxCommandEvent& event)
{
    //STOP BUTTON
    stop_thread = true;
    Button3->SetLabel("Continue");
    Button3->Enable(true);
    Button5->Enable(true);

}

void SortingVisualisationFrame::OnButton5Click(wxCommandEvent& event)
{
    Button5->Enable(false);
    Button3->SetLabel("Start");
    Button3->Enable(false);
    Button2->Enable(true);
    heights.clear();
    wxClientDC dc(Panel1);
    dc.Clear();

    // Pobierz rozmiary panelu
    int panelWidth, panelHeight;
    Panel1->GetSize(&panelWidth, &panelHeight);

    // Oblicz rozmiary i polozenie prostokatów
    int rectWidth = 20;
    int rectHeight = -500; //-10
    int rectSpacing = 2;
    int rectX = panelWidth - (panelWidth - 30);
    int rectY = panelHeight - 10;

    // Ustaw kolor i styl rysowania
    dc.SetPen(wxPen(wxColour(255, 0, 0), 1)); // Czerwony kolor, grubosc linii 2 piksele

    // Narysuj prostokaty obok siebie
    for (int i = 1; i <= 50; i++)
    {
        dc.DrawRectangle(rectX, rectY, rectWidth, rectHeight);
        heights.push_back(rectHeight);
        rectX += rectWidth+ rectSpacing;
        rectHeight += 10;
    }
}
