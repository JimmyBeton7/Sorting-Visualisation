/***************************************************************
 * Name:      SortingVisualisationApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2023-07-14
 * Copyright:  ()
 * License:
 **************************************************************/

#include "SortingVisualisationApp.h"

//(*AppHeaders
#include "SortingVisualisationMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SortingVisualisationApp);

bool SortingVisualisationApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SortingVisualisationFrame* Frame = new SortingVisualisationFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
