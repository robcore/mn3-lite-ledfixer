
/*
*		index : 0 ~ 255
*		300 is max CANDELA
*		(300*((index/255)^1.8))*4194304
*/

static int curve_1p8[] = {
0 ,
58615 ,
204109 ,
423474 ,
710750 ,
1062074 ,
1474623 ,
1946190 ,
2474975 ,
3059464 ,
3698357 ,
4390517 ,
5134937 ,
5930712 ,
6777028 ,
7673139 ,
8618364 ,
9612069 ,
10653673 ,
11742628 ,
12878427 ,
14060590 ,
15288668 ,
16562235 ,
17880888 ,
19244244 ,
20651938 ,
22103629 ,
23598982 ,
25137682 ,
26719425 ,
28343919 ,
30010886 ,
31720053 ,
33471168 ,
35263978 ,
37098242 ,
38973728 ,
40890208 ,
42847466 ,
44845289 ,
46883469 ,
48961818 ,
51080138 ,
53238234 ,
55435936 ,
57673056 ,
59949422 ,
62264862 ,
64619230 ,
67012349 ,
69444068 ,
71914232 ,
74422698 ,
76969312 ,
79553934 ,
82176431 ,
84836660 ,
87534495 ,
90269794 ,
93042439 ,
95852303 ,
98699250 ,
101583182 ,
104503970 ,
107461495 ,
110455645 ,
113486311 ,
116553383 ,
119656753 ,
122796303 ,
125971949 ,
129183586 ,
132431097 ,
135714407 ,
139033389 ,
142387981 ,
145778044 ,
149203540 ,
152664332 ,
156160368 ,
159691523 ,
163257734 ,
166858913 ,
170494960 ,
174165810 ,
177871365 ,
181611560 ,
185386307 ,
189195520 ,
193039134 ,
196917061 ,
200829227 ,
204775568 ,
208755996 ,
212770461 ,
216818862 ,
220901149 ,
225017233 ,
229167052 ,
233350556 ,
237567656 ,
241818290 ,
246102394 ,
250419905 ,
254770762 ,
259154875 ,
263572219 ,
268022707 ,
272506288 ,
277022899 ,
281572478 ,
286154960 ,
290770284 ,
295418412 ,
300099268 ,
304812814 ,
309558963 ,
314337688 ,
319148916 ,
323992594 ,
328868662 ,
333777092 ,
338717810 ,
343690766 ,
348695921 ,
353733200 ,
358802566 ,
363903956 ,
369037343 ,
374202654 ,
379399862 ,
384628905 ,
389889732 ,
395182294 ,
400506539 ,
405862443 ,
411249943 ,
416669000 ,
422119578 ,
427601575 ,
433115030 ,
438659816 ,
444235933 ,
449843340 ,
455482037 ,
461151855 ,
466852879 ,
472584982 ,
478348166 ,
484142387 ,
489967562 ,
495823691 ,
501710733 ,
507628644 ,
513577383 ,
519556909 ,
525567137 ,
531608109 ,
537679742 ,
543781951 ,
549914820 ,
556078182 ,
562272078 ,
568496426 ,
574751265 ,
581036472 ,
587352045 ,
593697943 ,
600074124 ,
606480588 ,
612917251 ,
619384070 ,
625881089 ,
632408181 ,
638965388 ,
645552627 ,
652169854 ,
658817071 ,
665494193 ,
672201305 ,
678938238 ,
685705034 ,
692501652 ,
699328008 ,
706184143 ,
713069932 ,
719985459 ,
726930597 ,
733905389 ,
740909751 ,
747943682 ,
755007100 ,
762100046 ,
769222435 ,
776374269 ,
783555504 ,
790766100 ,
798006056 ,
805275288 ,
812573839 ,
819901623 ,
827258600 ,
834644811 ,
842060173 ,
849504685 ,
856978306 ,
864480993 ,
872012747 ,
879573525 ,
887163286 ,
894782029 ,
902429713 ,
910106296 ,
917811778 ,
925546117 ,
933309270 ,
941101238 ,
948922021 ,
956771535 ,
964649739 ,
972556715 ,
980492296 ,
988456566 ,
996449442 ,
1004470922 ,
1012520966 ,
1020599573 ,
1028706701 ,
1036842309 ,
1045006354 ,
1053198878 ,
1061419840 ,
1069669197 ,
1077946949 ,
1086253013 ,
1094587389 ,
1102950076 ,
1111341033 ,
1119760259 ,
1128207714 ,
1136683395 ,
1145187221 ,
1153719232 ,
1162279387 ,
1170867560 ,
1179483919 ,
1188128337 ,
1196800774 ,
1205501228 ,
1214229701 ,
1222986149 ,
1231770532 ,
1240582849 ,
1249423099 ,
1258291200 ,
};

/*
*		index : 0 ~ 255
*		350 is max CANDELA
*		(350*((index/255)^1.8))*4194304
*/

static int curve_1p8_350[] = {
0 ,
68384 ,
238128 ,
494053 ,
829208 ,
1239086 ,
1720394 ,
2270555 ,
2887471 ,
3569375 ,
4314750 ,
5122270 ,
5990760 ,
6919165 ,
7906533 ,
8951996 ,
10054758 ,
11214081 ,
12429285 ,
13699733 ,
15024831 ,
16404022 ,
17836780 ,
19322608 ,
20861036 ,
22451618 ,
24093928 ,
25787567 ,
27532146 ,
29327296 ,
31172662 ,
33067905 ,
35012700 ,
37006728 ,
39049695 ,
41141308 ,
43281283 ,
45469351 ,
47705242 ,
49988709 ,
52319505 ,
54697382 ,
57122121 ,
59593493 ,
62111275 ,
64675258 ,
67285230 ,
69940992 ,
72642342 ,
75389100 ,
78181072 ,
81018078 ,
83899938 ,
86826480 ,
89797532 ,
92812922 ,
95872503 ,
98976104 ,
102123576 ,
105314762 ,
108549514 ,
111827686 ,
115149126 ,
118513713 ,
121921295 ,
125371744 ,
128864919 ,
132400697 ,
135978946 ,
139599544 ,
143262355 ,
146967271 ,
150714186 ,
154502947 ,
158333474 ,
162205622 ,
166119311 ,
170074384 ,
174070797 ,
178108385 ,
182187094 ,
186306777 ,
190467354 ,
194668730 ,
198910786 ,
203193443 ,
207516592 ,
211880153 ,
216284025 ,
220728109 ,
225212323 ,
229736572 ,
234300767 ,
238904830 ,
243548662 ,
248232207 ,
252955337 ,
257718007 ,
262520103 ,
267361563 ,
272242315 ,
277162268 ,
282121336 ,
287119461 ,
292156556 ,
297232557 ,
302347352 ,
307500922 ,
312693156 ,
317924003 ,
323193382 ,
328501224 ,
333847456 ,
339231998 ,
344654814 ,
350115810 ,
355614950 ,
361152123 ,
366727301 ,
372340404 ,
377991360 ,
383680107 ,
389406607 ,
395170781 ,
400972560 ,
406811908 ,
412688736 ,
418602994 ,
424554623 ,
430543586 ,
436569752 ,
442633164 ,
448733737 ,
454871346 ,
461045991 ,
467257629 ,
473506177 ,
479791594 ,
486113836 ,
492472820 ,
498868504 ,
505300847 ,
511769806 ,
518275256 ,
524817237 ,
531395710 ,
538010504 ,
544661706 ,
551349146 ,
558072867 ,
564832785 ,
571628816 ,
578461001 ,
585329216 ,
592233418 ,
599173607 ,
606149741 ,
613161653 ,
620209468 ,
627293018 ,
634412304 ,
641567283 ,
648757872 ,
655984112 ,
663245837 ,
670543129 ,
677875863 ,
685244039 ,
692647614 ,
700086464 ,
707560672 ,
715070112 ,
722614742 ,
730194604 ,
737809531 ,
745459606 ,
753144703 ,
760864823 ,
768619923 ,
776409920 ,
784234856 ,
792094604 ,
799989207 ,
807918581 ,
815882683 ,
823881472 ,
831914907 ,
839983028 ,
848085710 ,
856222954 ,
864394716 ,
872600956 ,
880841631 ,
889116741 ,
897426160 ,
905769973 ,
914148095 ,
922560443 ,
931007058 ,
939487857 ,
948002798 ,
956551880 ,
965135061 ,
973752301 ,
982403556 ,
991088827 ,
999808030 ,
1008561165 ,
1017348190 ,
1026169105 ,
1035023826 ,
1043912353 ,
1052834645 ,
1061790700 ,
1070780394 ,
1079803810 ,
1088860822 ,
1097951473 ,
1107075678 ,
1116233437 ,
1125424709 ,
1134649493 ,
1143907706 ,
1153199306 ,
1162524334 ,
1171882749 ,
1181274467 ,
1190699488 ,
1200157811 ,
1209649353 ,
1219174072 ,
1228732052 ,
1238323167 ,
1247947417 ,
1257604760 ,
1267295154 ,
1277018642 ,
1286775096 ,
1296564560 ,
1306386990 ,
1316242346 ,
1326130628 ,
1336051751 ,
1346005757 ,
1355992604 ,
1366012167 ,
1376064572 ,
1386149734 ,
1396267570 ,
1406418121 ,
1416601304 ,
1426817160 ,
1437065607 ,
1447346643 ,
1457660268 ,
1468006400 ,
};

/*
*		index : 0 ~ 255
*		300 is max CANDELA
*		(300*((index/255)^1.85))*4194304
*/

static int curve_1p85[] = {
0 ,
44431 ,
160172 ,
339122 ,
577421 ,
872522 ,
1222536 ,
1625972 ,
2081605 ,
2588395 ,
3145443 ,
3751961 ,
4407245 ,
5110660 ,
5861634 ,
6659638 ,
7504190 ,
8394838 ,
9331167 ,
10312786 ,
11339328 ,
12410450 ,
13525825 ,
14685148 ,
15888125 ,
17134477 ,
18423939 ,
19756262 ,
21131200 ,
22548524 ,
24008010 ,
25509443 ,
27052619 ,
28637334 ,
30263406 ,
31930645 ,
33638874 ,
35387919 ,
37177611 ,
39007792 ,
40878301 ,
42788981 ,
44739693 ,
46730289 ,
48760625 ,
50830569 ,
52939985 ,
55088744 ,
57276715 ,
59503781 ,
61769817 ,
64074713 ,
66418339 ,
68800595 ,
71221366 ,
73680537 ,
76178019 ,
78713698 ,
81287470 ,
83899246 ,
86548918 ,
89236397 ,
91961583 ,
94724392 ,
97524732 ,
100362514 ,
103237651 ,
106150054 ,
109099644 ,
112086332 ,
115110035 ,
118170690 ,
121268200 ,
124402503 ,
127573514 ,
130781150 ,
134025365 ,
137306044 ,
140623152 ,
143976611 ,
147366347 ,
150792284 ,
154254359 ,
157752521 ,
161286671 ,
164856783 ,
168462782 ,
172104591 ,
175782148 ,
179495403 ,
183244306 ,
187028768 ,
190848738 ,
194704180 ,
198595018 ,
202521201 ,
206482667 ,
210479377 ,
214511257 ,
218578243 ,
222680310 ,
226817395 ,
230989448 ,
235196419 ,
239438244 ,
243714874 ,
248026258 ,
252372371 ,
256753149 ,
261168531 ,
265618490 ,
270102952 ,
274621903 ,
279175269 ,
283763024 ,
288385105 ,
293041487 ,
297732107 ,
302456928 ,
307215911 ,
312009007 ,
316836164 ,
321697371 ,
326592551 ,
331521680 ,
336484721 ,
341481622 ,
346512345 ,
351576842 ,
356675098 ,
361807051 ,
366972676 ,
372171923 ,
377404753 ,
382671142 ,
387971027 ,
393304395 ,
398671208 ,
404071417 ,
409504995 ,
414971905 ,
420472097 ,
426005559 ,
431572239 ,
437172096 ,
442805130 ,
448471258 ,
454170478 ,
459902749 ,
465668030 ,
471466278 ,
477297535 ,
483161675 ,
489058699 ,
494988564 ,
500951270 ,
506946734 ,
512974955 ,
519035934 ,
525129587 ,
531255913 ,
537414871 ,
543606461 ,
549830598 ,
556087242 ,
562376433 ,
568698130 ,
575052249 ,
581438789 ,
587857710 ,
594309053 ,
600792692 ,
607308627 ,
613856859 ,
620437344 ,
627050084 ,
633694994 ,
640372032 ,
647081283 ,
653822620 ,
660596001 ,
667401511 ,
674239024 ,
681108581 ,
688010098 ,
694943534 ,
701908931 ,
708906246 ,
715935397 ,
722996424 ,
730089327 ,
737213982 ,
744370429 ,
751558627 ,
758778492 ,
766030150 ,
773313433 ,
780628383 ,
787975001 ,
795353159 ,
802762942 ,
810204266 ,
817677132 ,
825181497 ,
832717403 ,
840284724 ,
847883503 ,
855513697 ,
863175264 ,
870868247 ,
878592561 ,
886348207 ,
894135142 ,
901953366 ,
909802880 ,
917683600 ,
925595567 ,
933538698 ,
941513035 ,
949518535 ,
957555115 ,
965622859 ,
973721683 ,
981851502 ,
990012443 ,
998204422 ,
1006427355 ,
1014681326 ,
1022966209 ,
1031282088 ,
1039628837 ,
1048006497 ,
1056415070 ,
1064854513 ,
1073324784 ,
1081825884 ,
1090357811 ,
1098920483 ,
1107513898 ,
1116138100 ,
1124793047 ,
1133478695 ,
1142195004 ,
1150941974 ,
1159719603 ,
1168527893 ,
1177366760 ,
1186236245 ,
1195136306 ,
1204066902 ,
1213028033 ,
1222019740 ,
1231041855 ,
1240094506 ,
1249177648 ,
1258291200 ,
};

/*
*		index : 0 ~ 255
*		350 is max CANDELA
*		(350*((index/255)^1.85))*4194304
*/

static int curve_1p85_350[] = {
0 ,
51836 ,
186868 ,
395643 ,
673658 ,
1017942 ,
1426292 ,
1896968 ,
2428539 ,
3019794 ,
3669684 ,
4377288 ,
5141785 ,
5962437 ,
6838573 ,
7769578 ,
8754888 ,
9793978 ,
10886361 ,
12031583 ,
13229216 ,
14478858 ,
15780129 ,
17132672 ,
18536145 ,
19990223 ,
21494595 ,
23048972 ,
24653067 ,
26306612 ,
28009345 ,
29761017 ,
31561389 ,
33410223 ,
35307307 ,
37252420 ,
39245353 ,
41285905 ,
43373881 ,
45509092 ,
47691350 ,
49920476 ,
52196310 ,
54518671 ,
56887395 ,
59302333 ,
61763316 ,
64270201 ,
66822833 ,
69421079 ,
72064786 ,
74753830 ,
77488064 ,
80267360 ,
83091595 ,
85960625 ,
88874353 ,
91832646 ,
94835382 ,
97882451 ,
100973737 ,
104109131 ,
107288514 ,
110511790 ,
113778855 ,
117089600 ,
120443923 ,
123841729 ,
127282916 ,
130767389 ,
134295042 ,
137865804 ,
141479570 ,
145136252 ,
148835767 ,
152578009 ,
156362923 ,
160190385 ,
164060344 ,
167972715 ,
171927407 ,
175924331 ,
179963416 ,
184044608 ,
188167785 ,
192332914 ,
196539910 ,
200788689 ,
205079173 ,
209411306 ,
213785025 ,
218200227 ,
222656859 ,
227154877 ,
231694188 ,
236274732 ,
240896444 ,
245559273 ,
250263131 ,
255007950 ,
259793697 ,
264620292 ,
269487689 ,
274395822 ,
279344618 ,
284334020 ,
289363968 ,
294434432 ,
299545339 ,
304696619 ,
309888241 ,
315120111 ,
320392221 ,
325704483 ,
331056859 ,
336449291 ,
341881737 ,
347354125 ,
352866418 ,
358418561 ,
364010508 ,
369642191 ,
375313599 ,
381024643 ,
386775294 ,
392565505 ,
398395227 ,
404264401 ,
410172984 ,
416120947 ,
422108211 ,
428134797 ,
434200558 ,
440305535 ,
446449687 ,
452632846 ,
458855138 ,
465116395 ,
471416659 ,
477755846 ,
484133873 ,
490550780 ,
497006485 ,
503500945 ,
510034119 ,
516605964 ,
523216481 ,
529865544 ,
536553193 ,
543279389 ,
550044005 ,
556847124 ,
563688621 ,
570568454 ,
577486664 ,
584443127 ,
591437842 ,
598470809 ,
605541945 ,
612651206 ,
619798594 ,
626984023 ,
634207538 ,
641469010 ,
648768442 ,
656105831 ,
663481137 ,
670894276 ,
678345247 ,
685834009 ,
693360562 ,
700924822 ,
708526746 ,
716166335 ,
723843589 ,
731558424 ,
739310798 ,
747100711 ,
754928163 ,
762793028 ,
770695349 ,
778635082 ,
786612187 ,
794626663 ,
802678427 ,
810767478 ,
818893732 ,
827057274 ,
835257977 ,
843495841 ,
851770868 ,
860082972 ,
868432153 ,
876818370 ,
885241581 ,
893701828 ,
902198985 ,
910733135 ,
919304153 ,
927912040 ,
936556794 ,
945238332 ,
953956654 ,
962711760 ,
971503609 ,
980332157 ,
989197406 ,
998099313 ,
1007037794 ,
1016012934 ,
1025024647 ,
1034072894 ,
1043157672 ,
1052278941 ,
1061436701 ,
1070630867 ,
1079861481 ,
1089128502 ,
1098431888 ,
1107771596 ,
1117147628 ,
1126559981 ,
1136008616 ,
1145493447 ,
1155014517 ,
1164571826 ,
1174165248 ,
1183794866 ,
1193460598 ,
1203162443 ,
1212900316 ,
1222674261 ,
1232484277 ,
1242330279 ,
1252212269 ,
1262130205 ,
1272084085 ,
1282073868 ,
1292099555 ,
1302161145 ,
1312258555 ,
1322391783 ,
1332560831 ,
1342765657 ,
1353006218 ,
1363282514 ,
1373594546 ,
1383942272 ,
1394325691 ,
1404744719 ,
1415199400 ,
1425689689 ,
1436215505 ,
1446776930 ,
1457373923 ,
1468006400 ,
};
