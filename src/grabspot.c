/*
 * Tlf - contest logging program for amateur radio operators
 * Copyright (C) 2001-2002-2003 Rein Couperus <pa0r@eudxf.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "grabspot.h"

int send_bandswitch (int outfreq);

int grabspot (void) {

extern char hiscall[];
extern char *bandmap[];
extern int nroflines;
extern int trx_control;

extern float mem;

#ifdef HAVE_LIBHAMLIB
extern freq_t outfreq;
extern freq_t freq;
#else
extern int outfreq;
extern float freq;
#endif

int i, j, x;
char bufferstr[81];
char dupecall[17];

if (trx_control == 0)
	return(0);


if (hiscall[0] != '\0') {

	for (i = 0; i < nroflines; i++) {

		strcpy (bufferstr, bandmap[i]);

		if (strstr(bufferstr + 26, hiscall) != NULL) {

			outfreq = (int) (atof(bufferstr + 16) * 1000)    ;
			send_bandswitch (outfreq);

			strncpy(hiscall, bufferstr+26, 12);


			 for(j=0;  j <= 12; j++) {
				if (hiscall[j] == ' '){
					hiscall[j]='\0';
					break;
				}
			 }
			strncpy(dupecall,  hiscall, 16);

			x =  getctydata(dupecall);

			showinfo(x);

			searchlog(hiscall);
			refresh();


		 }
	}
}  else if (nroflines > 0){
	strcpy (bufferstr, bandmap[nroflines-1]);

	outfreq = (int) (atof(bufferstr + 16) * 1000)    ;

	strncpy(hiscall, bufferstr+26, 12);

	for(j=0;  j <= 12; j++) {
		if (hiscall[j] == ' '){
			hiscall[j]='\0';
			break;
		}
	 }
			strncpy(dupecall,  hiscall, 16);

			x =  getctydata(dupecall);

			showinfo(x);

			searchlog(hiscall);

				     	mem = freq;

				     	if (freq >= 7300.0)
				     		mvprintw(14, 68, "MEM: %5.1f",mem);
				     	else
				     		mvprintw(14, 68, "MEM:  %5.1f",mem);

			refresh();


}  else ;


 return(0);
}

