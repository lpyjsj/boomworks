/**
 * @file PasCounter.cpp
 * @brief implementation of the PascalCounter class.
 * @author Boom( boomworks@hotmail.com )
 * @author Copyright(C) 2004-2005 boomworks.org , All right reserved.
 * $Author: $
 * $Date: $
 * $Revision: $
 * $ID: $
 */

#include <wx/textfile.h>

#include "PasCounter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

wxString PascalCounter::ms_strType = _T("Pascal");

PascalCounter::PascalCounter()
{}

PascalCounter::~PascalCounter()
{}

void PascalCounter::countingSourceFile( wxTextFile& file, int& nLines, int& nCodeLines, int& nCommentLines, int& nBlankLines )
{
	BOOL bHasSettedCommentFlag	= FALSE;	//AΛΞRΔ΄ o"{"―TRUE, "}"―FALSE
    BOOL bHasSettedQuatoFlag	= FALSE;	//u¬RΔ΄ ΥΜΉΞoδϋτ"―TRUE, aΉΞoδϋτ"―FALSE

    wxString bufCurLine;
    for ( bufCurLine = file.GetFirstLine(); !file.Eof(); bufCurLine = file.GetNextLine() )
    {
        //BOOL bStatisticedAsComment	= FALSE;	//]Ξ¨AΛΞΕΟRΔ
        //BOOL bStatisticedAsCode		= FALSE;	//]Ξ¨ψιΞΕΟRΔ

        nLines++;

        bufCurLine.Trim(false); //gJΒόVctοΔ£

        if ( bufCurLine.Len() == 0 )
        { //¨tΥΞ OK
            nBlankLines++;
            continue;
        }

        //////////////////////////////////////////////////////////////////////////

        bufCurLine.Trim();
        int nLen = bufCurLine.Len();
        if ( !bHasSettedCommentFlag
                && bufCurLine[ 0 ]			==  _T( '{' )
                && bufCurLine[ nLen - 1 ]	==  _T( '}' ))
        {
            nCommentLines++;
            continue;
        }
        else if ( !bHasSettedCommentFlag
                  && bufCurLine.Find( _T( "{" )) != -1
                  && bufCurLine.Find( _T( "}" )) != -1 )
        {
            nCommentLines++;
            nCodeLines++;
            continue;
        }

        if ( !bHasSettedCommentFlag )
        {
            if ( bufCurLine[0]	== _T( '/' )
                    && bufCurLine[1]		== _T( '/' ) )
            {
                nCommentLines++;
                continue;
            }
            else if ( bufCurLine.Find( _T( "//" )) != -1 )
            { // ΫΉ[Ε ΉΞνo''cΘΰ
                nCommentLines++;
                nCodeLines++;
                continue;
            }
        }

        //////////////////////////////////////////////////////////////////////////
        if ( !bHasSettedCommentFlag
                && bufCurLine[0] == _T('{')
                && bufCurLine.Find( _T( '}' )) == -1 )
        {
            bHasSettedCommentFlag = TRUE;
            nCommentLines++;
            continue;
        }

        if (bHasSettedCommentFlag
                && bufCurLine[nLen - 1] != _T('}') )
        {
            nCommentLines++;
            continue;
        }
        else if ( bHasSettedCommentFlag
                  && bufCurLine[nLen - 1] == _T('}'))
        {
            bHasSettedCommentFlag = FALSE;
            nCommentLines++;
            continue;
        }

        //////////////////////////////////////////////////////////////////////////

        if ( bufCurLine.Find( _T( "//" ) ) == -1
                && bufCurLine.Find( _T( "{" ) ) == -1
                && bufCurLine.Find( _T( "}" ) ) == -1 )
        { //ε]Ξχ]ΛάAΛEπ¨ΉΕAΛΞE¨ΉΕψιΞ
            if ( bHasSettedCommentFlag )
            {
                nCommentLines++;
                continue;
            }
            else
            {
                nCodeLines++;
                continue;
            }
        }

        //////////////////////////////////////////////////////////////////////////

        if ( bufCurLine.Find( _T( "//" ) ) == 0 && !bHasSettedCommentFlag && !bHasSettedQuatoFlag )
        { // single line comment
            nCommentLines++;
            continue;
        }

	}// End for
}
