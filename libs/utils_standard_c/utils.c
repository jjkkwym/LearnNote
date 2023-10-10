#include "string.h"
#include <stdint.h>

static inline int wiced_bt_utils_isupper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

static inline int
wiced_bt_utils_isalpha(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

static inline int
wiced_bt_utils_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\12');
}

static inline int
wiced_bt_utils_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

//
// Implementation of standard string manipulation functions
//
// Note:  strlen strncpy strcmp and strstr defined in chip ROMs
//        strchr defined in all chip ROMs except 20706A2 and 43012C0

int utl_strncmp(const char *s1, const char *s2, int n)
{
    for ( ; n > 0; s1++, s2++, --n)
    if (*s1 != *s2)
        return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
    else if (*s1 == '\0')
        return 0;
    return 0;
}

char *utl_strcpy(char *p_dst, const char *p_src)
{
    register char *pd = p_dst;
    register const char *ps = p_src;

    while ( *ps )
        *pd++ = *ps++;

    *pd++ = 0;
    return ( p_dst );
}

char *utl_strcat(char *s1, const char *s2)
{
    utl_strcpy(&s1[strlen(s1)], (char *)s2);
    return s1;
}

char *utl_strrchr(char *s, int c)
{
    char* ret=0;
    do {
        if( *s == (char)c )
            ret=s;
    } while(*s++);
    return ret;
}

char *utl_strchr(const char *s, int c)
{
    const char ch = c;

    for ( ; *s != ch; s++)
        if (*s == '\0')
            return 0;
    return (char *)s;
}

char utl_toupper(char c)
{
    if( c>='a' && c<='z')
        return (c = c +'A' - 'a');
    else
        return c;
}

/*******************************************************************************
** Function         utl_str2int
** Description      This utility function converts a character string to an
**                  integer.  Acceptable values in string are 0-9.  If invalid
**                  string or string value too large, -1 is returned.  Leading
**                  spaces are skipped.
** Returns          Integer value or -1 on error.
*******************************************************************************/
uint16_t utl_str2int(const char *p_s)
{
    uint32_t val = 0;

    for (;*p_s == ' ' && *p_s != 0; p_s++);

    if (*p_s == 0) return -1;

    for (;;)
    {
        if ((*p_s < '0') || (*p_s > '9')) return -1;

        val += (uint32_t) (*p_s++ - '0');

        if (val > 32767) return -1;

        if (*p_s == 0)
        {
            return (uint16_t) val;
        }
        else
        {
            val *= 10;
        }
    }
}

/*******************************************************************************
** Function         utl_itoa
** Description      This utility function converts a UINT16 to a string
**                  The string is NULL-terminated
** Returns          Length of string
*******************************************************************************/
uint8_t utl_itoa(uint16_t i, char *p_s)
{
    uint16_t    j, k;
    char        *p = p_s;
    int         fill = 0;

    if (i == 0)
    {
        /* take care of zero case */
        *p++ = '0';
    }
    else
    {
        for(j = 10000; j > 0; j /= 10)
        {
            k = i / j;
            i %= j;
            if (k > 0 || fill)
            {
              *p++ = k + '0';
              fill = 1;
            }
        }
    }
    *p = 0;
    return (uint8_t) (p - p_s);
}

/*******************************************************************************
** Function         utl_strucmp
** Description      This utility function compares two strings in uppercase.
**                  String p_s must be uppercase.  String p_t is converted to
**                  uppercase if lowercase.  If p_s ends first, the substring
**                  match is counted as a match.
** Returns          0 if strings match, nonzero otherwise.
*******************************************************************************/
int utl_strucmp(const char *p_s, const char *p_t)
{
    char c;

    while (*p_s && *p_t)
    {
        c = *p_t++;
        if (c >= 'a' && c <= 'z')
        {
            c -= 0x20;
        }
        if (*p_s++ != c)
        {
            return -1;
        }
    }
    /* if p_t hit null first, no match */
    if (*p_t == 0 && *p_s != 0)
    {
        return 1;
    }
    /* else p_s hit null first, count as match */
    else
    {
        return 0;
    }
}
