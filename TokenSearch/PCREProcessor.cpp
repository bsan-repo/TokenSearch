//
//  PCREProcessor.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "PCREProcessor.h"
#include "StrHelper.h"
#include <pcre.h>
#include <list>


#define OVECCOUNT 30 

bool PCREProcessor::match(char* pattern, char* subject, int** results, int* resultsSize, char** errorMsg){
    pcre *re;
    const char *error;
    unsigned int option_bits;
    int erroffset;
    int crlf_is_newline;
    int ovector[OVECCOUNT];
    int subject_length;
    int rc;
    int utf8;
    char errorBuffer[200];
    std::list<int> resultsList;
    
    printf("PATTERN: %s\n", pattern);
    printf("SUBJECT: %s\n", subject);
    // ----------------------------------------------------------------------------
    
    subject_length = (int)strlen(subject);
    
    // compile ------------------------------------------
    re = pcre_compile(
                      pattern,
                      0,
                      &error,
                      &erroffset,
                      NULL);
    
    if (re == NULL)
    {
        sprintf(errorBuffer, "PCRE compilation failed at offset %d: %s\n", erroffset, error);
        StrHelper::copyString(errorMsg, errorBuffer);
        return false;
    }
    
    // Configure new line
    (void)pcre_fullinfo(re, NULL, PCRE_INFO_OPTIONS, &option_bits);
    utf8 = option_bits & PCRE_UTF8;
    option_bits &= PCRE_NEWLINE_CR|PCRE_NEWLINE_LF|PCRE_NEWLINE_CRLF|
    PCRE_NEWLINE_ANY|PCRE_NEWLINE_ANYCRLF;
    
    // If no newline options were set, find the default newline convention from the build configuration.
    
    if (option_bits == 0)
    {
        int d;
        (void)pcre_config(PCRE_CONFIG_NEWLINE, &d);
        option_bits = (d == 13)? PCRE_NEWLINE_CR :
        (d == 10)? PCRE_NEWLINE_LF :
        (d == (13<<8 | 10))? PCRE_NEWLINE_CRLF :
        (d == -2)? PCRE_NEWLINE_ANYCRLF :
        (d == -1)? PCRE_NEWLINE_ANY : 0;
    }
    
    /* See if CRLF is a valid newline sequence. */
    
    crlf_is_newline =
    option_bits == PCRE_NEWLINE_ANY ||
    option_bits == PCRE_NEWLINE_CRLF ||
    option_bits == PCRE_NEWLINE_ANYCRLF;
    
    /* Loop for matches */
    int start_offset = 0;
    
    for (;;)
    {
        int options = 0;
        
        rc = pcre_exec(
                       re,
                       NULL,
                       subject,
                       subject_length,
                       start_offset,
                       options,
                       ovector,
                       OVECCOUNT);
        
        /* PCRE DOC
         This time, a result of NOMATCH isn't an error. If the value in "options"
         is zero, it just means we have found all possible matches, so the loop ends.
         Otherwise, it means we have failed to find a non-empty-string match at a
         point where there was a previous empty-string match. In this case, we do what
         Perl does: advance the matching position by one character, and continue. We
         do this by setting the "end of previous match" offset, because that is picked
         up at the top of the loop as the point at which to start again.
         
         There are two complications: (a) When CRLF is a valid newline sequence, and
         the current position is just before it, advance by an extra byte. (b)
         Otherwise we must ensure that we skip an entire UTF-8 character if we are in
         UTF-8 mode. */
        
        if (rc == PCRE_ERROR_NOMATCH)
        {
            if (options == 0)
                break;                    /* All matches found */
            
            ovector[1] = start_offset + 1;              /* Advance one byte */
            if (crlf_is_newline &&                      /* If CRLF is newline & */
                start_offset < subject_length - 1 &&    /* we are at CRLF, */
                subject[start_offset] == '\r' &&
                subject[start_offset + 1] == '\n')
                ovector[1] += 1;                          /* Advance by one more. */
            else if (utf8)                              /* Otherwise, ensure we */
            {                                         /* advance a whole UTF-8 */
                while (ovector[1] < subject_length)       /* character. */
                {
                    if ((subject[ovector[1]] & 0xc0) != 0x80)
                        break;
                    ovector[1] += 1;
                }
            }
            continue;    /* Go round the loop again */
        }
        
        /* Other matching errors are not recoverable. */
        if (rc < 0){
            sprintf(errorBuffer, "Matching error %d\n", rc);
            StrHelper::copyString(errorMsg, errorBuffer);
            pcre_free(re);    /* Release memory used for the compiled pattern */
            return false;
        }
        
        if (rc == 0)
        {
            rc = OVECCOUNT/3;
            sprintf(errorBuffer, "ovector only has room for %d captured substrings\n", rc - 1);
            StrHelper::copyString(errorMsg, errorBuffer);
        }
        
        /* As before, show substrings stored in the output vector by number, and then
         also any named substrings. */
        
        
        char *substring_start = subject + ovector[0]; // DEV
        int substring_length = ovector[1] - ovector[0]; // DEV
        printf("0: %.*s\n", substring_length, substring_start); // DEV
        
        // Copy first substring match
        int match_start = ovector[0];
        int match_length = ovector[1] - ovector[0];
        if(match_length > 0){
            resultsList.push_back(match_start);
            resultsList.push_back(match_length);
        }
        
        start_offset = ovector[1];
        
        if(match_length <= 0){
            if(start_offset+1<subject_length){
                start_offset = start_offset+1;
            }else{
                break;
            }
        }
    }
    
    *results = new int[resultsList.size()];
    int indexResults = 0;
    for (std::list<int>::iterator it = resultsList.begin(); it != resultsList.end(); it++) {
        *(*results+indexResults) = *it;
        indexResults++;
        (*resultsSize)++;
    }
    
    pcre_free(re);
    return true;
}