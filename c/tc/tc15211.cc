/* TopCoder https://arena.topcoder.com/#/u/practiceCode/17372/73137/15211/2/331921 */
#include "gtest/gtest.h"
#include <vector>
#include <map>
#include <set>

using namespace std;

class MaximizingGCD {
public:
	static set<int> allFactors(const vector<int> &A) {
		set<int> res;
		for (int i = 0; i < A.size(); i++) {
			for (int j = i + 1; j < A.size(); j++) {
				int a = A[i] + A[j];
				for (int n = 1; n * n <= a; n++) {
					if (a % n == 0) {
						res.insert(n);
						res.insert(a / n);
					}
				}
			}
		}
		return res;
	}
	static int maximumGCDPairing(vector <int> A) {
		int mx = -1;
		// try all potential divisors
		for (auto g:allFactors(A)) {
			map<int,int> rem;
			for (auto a:A) {
				int r = a % g;
				rem[r]++;
			}
			bool ans = !(rem[0] & 1);
			for (auto r:rem) {
				if (r.first > 0) {
					int br = g-r.first;
					if (r.first != br)
						ans &= (r.second == rem[br]);
					else
						ans &= !(r.second & 1);
				}
			}
			if (ans)
				mx = max(mx, g);
		}
		return mx;
	}
};

TEST(TC, TC0) {
	EXPECT_EQ(6, MaximizingGCD::maximumGCDPairing({5, 4, 13, 2}));
}

TEST(TC, TC1) {
	EXPECT_EQ(49, MaximizingGCD::maximumGCDPairing({26, 23}));
}

TEST(TC, TC2) {
	EXPECT_EQ(100, MaximizingGCD::maximumGCDPairing({100, 200, 300, 500, 1100, 700}));
}

TEST(TC, TC4) {
	EXPECT_EQ(4, MaximizingGCD::maximumGCDPairing({46, 78, 133, 92, 1, 23, 29, 67, 43, 111, 3908, 276, 13, 359, 20, 21}));
}

TEST(TC, TC5) {
	EXPECT_EQ(16400, MaximizingGCD::maximumGCDPairing({16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608}));
}

TEST(TC, TCC1) { EXPECT_EQ(6, MaximizingGCD::maximumGCDPairing({5, 4, 13, 2}));}
TEST(TC, TCC4) { EXPECT_EQ(49, MaximizingGCD::maximumGCDPairing({26, 23}));}
TEST(TC, TCC7) { EXPECT_EQ(100, MaximizingGCD::maximumGCDPairing({100, 200, 300, 500, 1100, 700}));}
TEST(TC, TCC10) { EXPECT_EQ(4, MaximizingGCD::maximumGCDPairing({46, 78, 133, 92, 1, 23, 29, 67, 43, 111, 3908, 276, 13, 359, 20, 21}));}
TEST(TC, TCC13) { EXPECT_EQ(16400, MaximizingGCD::maximumGCDPairing({16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608}));}
TEST(TC, TCC16) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));}
TEST(TC, TCC19) { EXPECT_EQ(2000000000, MaximizingGCD::maximumGCDPairing({1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000}));}
TEST(TC, TCC22) { EXPECT_EQ(1000000001, MaximizingGCD::maximumGCDPairing({1, 1000000000}));}
TEST(TC, TCC25) { EXPECT_EQ(6, MaximizingGCD::maximumGCDPairing({81, 367567119, 643242519, 581981319, 714713919, 892371399, 955674639, 964863819, 943422399, 969968919, 953512479, 832431519, 953512479, 872972019, 643242519, 832431519, 673873119, 775975119, 655855119, 655855119, 998917839, 698377599, 969968919, 554954319, 661620879, 892371399, 808647759, 810809919, 681080319, 857656719}));}
TEST(TC, TCC28) { EXPECT_EQ(10, MaximizingGCD::maximumGCDPairing({505, 796395095, 891890495, 554953895, 808647335, 581980895, 808647335, 808647335, 655854695, 953512055, 459458495, 943421975, 514593575, 714713495, 814773455, 892370975, 843241895, 796395095, 349188335, 349188335, 554953895, 937295855, 972971495, 673872695, 810809495, 892370975, 843241895, 972971495, 972971495, 937295855}));}
TEST(TC, TCC31) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({241, 713512559, 969968759, 367566959, 775974959, 551350559, 673872959, 882881759, 857656559, 714713759, 673872959, 998917679, 853572479, 612611759, 964863659, 972971759, 465584879, 698377439, 465584879, 771890879, 756755759, 698377439, 892371239, 655854959, 551350559, 551350559, 681080159, 796395359, 775974959, 969968759}));}
TEST(TC, TCC34) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({379, 612611621, 581981021, 643242221, 514593701, 832431221, 900539261, 349188461, 698377301, 814773581, 349188461, 853572341, 349188461, 832431221, 810809621, 853572341, 945944621, 459458621, 551350421, 857656421, 853572341, 945944621, 465584741, 853572341, 964863521, 953512181, 551350421, 983782421, 643242221, 428828021}));}
TEST(TC, TCC37) { EXPECT_EQ(6, MaximizingGCD::maximumGCDPairing({873, 853571847, 969968127, 349187967, 945944127, 554953527, 953511687, 367566327, 945944127, 716755167, 796394727, 349187967, 857655927, 756755127, 716755167, 612611127, 765764127, 955673847, 853571847, 814773087, 349187967, 771890247, 983781927, 716755167, 454052727, 794592927, 882881127, 832430727, 810809127, 551349927}));}
TEST(TC, TCC40) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({641, 927025459, 584022799, 206125279, 446185099, 842340859, 463782679, 409908859, 486004879, 842340859, 420419359, 105945199, 277476559, 780779359, 320165359, 261890989, 686069359, 257296399, 137213359, 756755359, 597296059, 243242359, 180179359, 960497359, 573872659, 393512479, 168647839, 174593779, 669277969, 713512159}));}
TEST(TC, TCC43) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({737, 422618383, 128065663, 343034263, 814773223, 555659263, 872070463, 264863863, 159278383, 264863863, 972010303, 449248063, 171530623, 398197063, 122244463, 590268943, 873179263, 981079363, 314473423, 663662263, 484983763, 102101263, 249728743, 689187763, 459458263, 364503403, 321620563, 756575083, 765764263, 422618383}));}
TEST(TC, TCC46) { EXPECT_EQ(330, MaximizingGCD::maximumGCDPairing({825, 556214835, 318557415, 494413095, 975974175, 730809255, 285237975, 365404215, 494413095, 972010215, 436485225, 73512615, 482431125, 654052575, 84323415, 594593175, 436485225, 339569175, 673872375, 918196455, 378377175, 73512615, 145529175, 707566035, 727475925, 413512275, 210209175, 303242115, 378377175, 611079645}));}
TEST(TC, TCC49) { EXPECT_EQ(18, MaximizingGCD::maximumGCDPairing({729, 274427271, 737175711, 527025771, 291059271, 168467571, 727649271, 332971911, 527025771, 950795271, 721439991, 611079741, 398197071, 693692271, 472971771, 445944771, 895944321, 272431431, 529728471, 164656071, 915674031, 79278471, 378377271, 536034771, 261953271, 929127471, 503117271, 81080271, 454052871, 291059271}));}
TEST(TC, TCC52) { EXPECT_EQ(14, MaximizingGCD::maximumGCDPairing({721, 693692279, 459458279, 554953679, 448231679, 196755839, 301870079, 426785639, 428106959, 644142779, 187109279, 124739279, 529728479, 763722239, 611079749, 85764959, 900899279, 346845779, 882671069, 84323519, 943421759, 220539599, 590268959, 608106779, 520719479, 158918039, 196755839, 457379279, 485584379, 503117279}));}
TEST(TC, TCC55) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({6752152, 250461971, 90085751, 424259329, 232686311, 27380194, 80789225, 62316721, 43530301, 12921991, 138883580, 47015821, 50315925, 181019419, 38947593, 33500881, 158626811, 331997911, 76231751, 97108239, 413216155, 10434853, 129648201, 198751437, 305177645, 277001533}));}
TEST(TC, TCC58) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({43108501, 323629811, 139517201, 69082511, 11142145, 154075614, 119227260, 163813685, 57692496, 92288956, 61400173, 73460311, 51557873, 264952519, 290404762, 400543786, 6322816, 71236945, 7139705, 270464923, 133282937, 249385256, 336264601, 43227063}));}
TEST(TC, TCC61) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({171006737, 289982233, 109000204, 93199405, 240878649, 198420526, 10711413, 102920401, 434362640, 182278981, 163766501, 15179437, 96199432, 39624567, 365730559, 32719915, 222621127, 33627534, 28577539, 382237, 75907417, 443565413, 357415141, 359968323, 223821145, 86329731}));}
TEST(TC, TCC64) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({31937254, 92726207, 126995716, 2087061, 274275739, 2286898, 1087703, 46536481, 132221761, 404712325, 119884891, 5357485, 92411089, 125941341, 261932308, 143746569, 145909837, 22261680, 273499651, 73820437, 149639150, 80139288, 127001631, 56094452, 42480593, 35789313, 204830425, 47000599}));}
TEST(TC, TCC67) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({29183131, 2369101, 94845521, 5784871, 11748815, 51699726, 42488551, 110903755, 209445576, 213956911, 34346561, 30933241, 42945624, 17378071, 216196746, 160469541, 137796646, 56441701, 60976501, 193494899, 111686956, 23681001, 72008473, 2670620, 324914437, 170293351}));}
TEST(TC, TCC70) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({201873823, 6025627, 176658651, 36024922, 98084305, 15338161, 35261929, 87901633, 220210393, 132000205, 64488672, 32354421, 2071485, 24506198, 61700572, 154557816, 54290489, 4619044, 20491409, 86858216, 66749467, 15414480, 219677437, 18961978}));}
TEST(TC, TCC73) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({243435313, 220484602, 122980201, 30388087, 109860870, 172675273, 394548096, 22057941, 112562309, 4781141, 147179845, 86264059, 23040883, 143912357, 456551191, 10232926, 266073473, 109924165, 12424604, 20151117, 33608449, 8749229, 32717064, 231994234, 248053393, 130922727, 468340629, 30557217, 33419101, 88326577}));}
TEST(TC, TCC76) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({74807773, 380602223, 15783371, 132516265, 257836941, 39548163, 432161367, 343981297, 117613651, 173496601, 30017612, 4468269, 178362118, 131025873, 14376034, 37395921, 56279151, 131892401, 69355568, 253953127, 236000051, 44937076, 11382001, 251580865, 57622921, 116280477}));}
TEST(TC, TCC79) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({6151944, 80406986, 132073621, 133504201, 256066302, 582002, 4461963, 106192522, 9157773, 38143396, 296741571, 431495418, 55202785, 41057713, 59591465, 122492281, 223799953, 127224469, 286498864, 105343680, 237572798, 56430183, 156646234, 297472939}));}
TEST(TC, TCC82) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({151060109, 105698689, 39609542, 146136722, 218309845, 172903431, 141739642, 97761683, 153208853, 155404351, 209226506, 397549678, 91553251, 10865845, 112647745, 29637043, 47408439, 69834227, 177758401, 69420877, 52708639, 166597597, 384859, 325692076, 141177829, 110639728, 99815041, 177642478, 299094181, 16913530}));}
TEST(TC, TCC85) { EXPECT_EQ(18, MaximizingGCD::maximumGCDPairing({640331532, 404323452, 208107432, 268938972, 346846032, 277476732, 252251532, 428107212, 428107212, 330329532, 171530892, 800414532, 561560532, 588587532, 360719892, 468, 97296732, 366735132, 142702092, 218294532, 895944582, 64864332, 218617932, 520719732, 405404532, 301870332, 640179072, 716755572}));}
TEST(TC, TCC88) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({491891039, 535134239, 819818639, 659578559, 180179639, 384198839, 594593639, 584023079, 393512759, 361, 480960119, 833489639, 618017039, 855716039, 709458389, 358377659, 416575799, 776935799, 485099639, 926099639, 876034799, 955674359, 494413559, 572791859, 85765319, 885404159}));}
TEST(TC, TCC91) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({90089686, 405404686, 314, 918917686, 412011286, 360720046, 387987286, 128648206, 632431486, 896464486, 972010726, 693692686, 316215586, 726725686, 142702246, 255254686, 873179686, 468467686, 79278886, 499458646, 113513086, 208107586, 189188686, 81080686, 396395686, 530930086, 590269366, 314473846, 936485236, 208107586}));}
TEST(TC, TCC94) { EXPECT_EQ(6, MaximizingGCD::maximumGCDPairing({950569398, 611080248, 721440498, 199098678, 163963578, 730809858, 198197778, 97296978, 808647618, 358377798, 972971778, 332972418, 494173458, 387987378, 981079878, 61260978, 926099778, 618017178, 441440778, 235855398, 222, 611080248, 993242028, 261953778}));}
TEST(TC, TCC97) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({832431599, 312432119, 459458999, 819818999, 842341499, 137837699, 128066399, 510509999, 737176439, 882881999, 794593799, 79279199, 199098899, 618017399, 450269819, 371651279, 981080099, 330329999, 85765679, 330329999, 554954399, 1, 468467999, 733471199}));}
TEST(TC, TCC100) { EXPECT_EQ(210210, MaximizingGCD::maximumGCDPairing({468648180, 244490400, 853572720, 804053250, 535134600, 989368380, 675404730, 158918760, 227026800, 698377680, 378378000, 346846500, 267567300, 716756040, 765164400, 950569620, 836215380, 347146800, 409909500, 824023200, 804053250, 168648480, 720373500, 662161500, 726726000, 964863900}));}
TEST(TC, TCC103) { EXPECT_EQ(9240, MaximizingGCD::maximumGCDPairing({285885600, 663663000, 97297200, 349188840, 400239840, 495495000, 842341500, 128066400, 252252000, 885224340, 261954000, 998917920, 142702560, 317837520, 989368380, 229729500, 527026500, 257657400, 269549280, 611080470, 669278610, 409909500, 609008400, 536035500, 541080540, 885404520}));}
TEST(TC, TCC106) { EXPECT_EQ(2310, MaximizingGCD::maximumGCDPairing({762300000, 794593800, 81081000, 982731750, 261891630, 609008400, 405405000, 407484000, 647446800, 582702120, 905612400, 142702560, 238918680, 486486000, 756756000, 314474160, 608107500, 202702500, 857656800, 409909500, 480960480, 294294000, 274428000, 184984800, 297297000, 556215660, 588588000, 993242250}));}
TEST(TC, TCC109) { EXPECT_EQ(2310, MaximizingGCD::maximumGCDPairing({845238240, 913512600, 523783260, 108108000, 315315000, 134774640, 353152800, 385945560, 386486100, 960498000, 390390000, 378378000, 477837360, 730810080, 436486050, 727650000, 208288080, 202161960, 306306000, 142942800, 990990000, 353152800, 330330000, 495495000, 541080540, 632431800}));}
TEST(TC, TCC112) { EXPECT_EQ(2310, MaximizingGCD::maximumGCDPairing({464564100, 814773960, 102102000, 576298800, 234234000, 918197280, 781080300, 288149400, 268939440, 582702120, 756756000, 714714000, 261891630, 192099600, 137837700, 75675600, 357357000, 364504140, 224624400, 138738600, 998917920, 630630000, 227026800, 315315000, 673873200, 567567000}));}
TEST(TC, TCC115) { EXPECT_EQ(420, MaximizingGCD::maximumGCDPairing({751500750, 60060000, 86276190, 200103750, 545044500, 506756250, 553429800, 215222700, 206756550, 584023440, 231231000, 575231580, 226380000, 480249000, 59729670, 223092870, 923662740, 381531150, 391314000, 243993750, 283423140, 187110000, 421170750, 461191500, 643242600, 809308500, 196546350, 71050980, 206756550, 201684000}));}
TEST(TC, TCC118) { EXPECT_EQ(420, MaximizingGCD::maximumGCDPairing({183028230, 208372500, 244490400, 356095740, 548107560, 764032500, 110990880, 155195040, 601200600, 253753500, 85571640, 61771710, 453212760, 374220000, 164351880, 941288040, 150935400, 66366300, 600311250, 232792560, 63243180, 109567920, 163513350, 664115760, 71050980, 356756400, 178047870, 121621500, 792330000, 382016250}));}
TEST(TC, TCC121) { EXPECT_EQ(420, MaximizingGCD::maximumGCDPairing({902581680, 784406700, 387400860, 741620880, 390540150, 908407500, 213929100, 811620810, 466754400, 187297110, 308700000, 148837500, 83243160, 305224920, 435781500, 650900250, 755795040, 991980990, 416576160, 106186080, 618377760, 446606160, 609008400, 450269820, 635885250, 200103750, 561561000, 431380950, 238140000, 716756040}));}
TEST(TC, TCC124) { EXPECT_EQ(420, MaximizingGCD::maximumGCDPairing({743242500, 599548950, 188948760, 450900450, 784864080, 224624400, 138858720, 380630250, 295134840, 793122330, 994713720, 71050980, 184294110, 192099600, 523908000, 781560780, 507310650, 486202500, 165915750, 555945390, 600359760, 274053780, 185405220, 87837750, 67897830, 636693750, 183783600, 393092700, 242792550, 207900000}));}
TEST(TC, TCC127) { EXPECT_EQ(4620, MaximizingGCD::maximumGCDPairing({712191480, 316932000, 972972000, 491891400, 743302560, 862847370, 195657000, 309188880, 164351880, 763062300, 267807540, 107026920, 141711570, 525314790, 78078000, 407386980, 896464800, 741260520, 79459380, 586971000, 923662740, 693693000, 882671790, 318558240, 999248250, 272522250, 147567420, 68708640, 473489940, 182702520}));}
TEST(TC, TCC130) { EXPECT_EQ(13860, MaximizingGCD::maximumGCDPairing({286936650, 95287500, 731981250, 424462500, 130180050, 636693750, 791710920, 927566640, 227026800, 746876130, 730029300, 378378000, 92492400, 319729410, 709458750, 432612180, 380630250, 607506900, 541080540, 205439850, 117927810, 693693000, 432401970, 440228250, 384199200, 74324250, 313762680, 873180000, 668918250, 158466000}));}
TEST(TC, TCC133) { EXPECT_EQ(210, MaximizingGCD::maximumGCDPairing({84234150, 85135050, 105105000, 905612400, 373527000, 136636500, 669909240, 76516440, 122522400, 485100000, 102910500, 277477200, 166698000, 657026370, 638137500, 993242250, 567236250, 551350800, 104186250, 144204060, 218017800, 498086820, 219135840, 710509800, 530930400, 406966560, 336936600, 704365200, 152806500, 436486050}));}
TEST(TC, TCC136) { EXPECT_EQ(210, MaximizingGCD::maximumGCDPairing({956455500, 810337500, 53603550, 644143500, 790539750, 63813750, 238378140, 113303190, 238378140, 588648060, 449248800, 614083470, 67387320, 139755000, 194481000, 144060000, 405168750, 737906400, 142702560, 228690000, 582702120, 475398000, 315131250, 212231250, 78618540, 117394200, 156881340, 304504200, 534822750, 136136700}));}
TEST(TC, TCC139) { EXPECT_EQ(210, MaximizingGCD::maximumGCDPairing({330660330, 68318250, 205439850, 228918690, 236185950, 405848520, 237699000, 485585100, 189078750, 956455500, 92492400, 112612500, 735735000, 848925000, 624323700, 101501400, 286936650, 653456160, 87837750, 567567000, 336936600, 64744680, 194594400, 213152940, 161700000, 190575000, 363363000, 206456250, 755795040, 166389300}));}
TEST(TC, TCC142) { EXPECT_EQ(210, MaximizingGCD::maximumGCDPairing({858858000, 324135000, 158482170, 618377760, 221371920, 902581680, 983782800, 113190000, 280145250, 387987600, 921470550, 204205050, 721020300, 865224360, 603741600, 608107500, 838530000, 594247500, 225645420, 204954750, 653456160, 377897520, 96996900, 325194870, 401711310, 514552500, 254100000, 115945830, 735735000, 158482170}));}
TEST(TC, TCC145) { EXPECT_EQ(211007609, MaximizingGCD::maximumGCDPairing({7590704, 44203977, 167114926, 52308657, 100001591, 147001086, 88399489, 52843529, 129997972, 111006018, 151001272, 60006337, 43892683, 158164080, 70328198, 177348922, 33658687, 151548209, 158698952, 140002198, 166803632, 122608120, 203416905, 81009637, 64006523, 71005411, 110990116, 59459400, 100017493, 140679411}));}
TEST(TC, TCC148) { EXPECT_EQ(100001591, MaximizingGCD::maximumGCDPairing({808758, 68997550, 7298981, 38696039, 19291240, 81004067, 89651111, 40024468, 99192833, 91007629, 73663234, 8993962, 24989208, 80710351, 92702610, 59977123, 97297200, 43441038, 2704391, 31004041, 11066591, 61305552, 76155037, 10350480, 56560553, 18997524, 88935000, 26338357, 75012383, 23846554}));}
TEST(TC, TCC151) { EXPECT_EQ(100017493, MaximizingGCD::maximumGCDPairing({93693600, 6635743, 6323893, 6462493, 51636279, 11007637, 7314883, 89733794, 90180090, 49110959, 93381750, 93555000, 89009856, 70874916, 89731862, 50016572, 50000921, 11007637, 29142577, 92702610, 57902029, 10283699, 28708355, 10285631, 48381214, 50906534, 9837403, 89009856, 71309138, 42115464}));}
TEST(TC, TCC154) { EXPECT_EQ(100003361, MaximizingGCD::maximumGCDPairing({8868224, 1770, 52722677, 69383698, 26847091, 7968807, 4974405, 21925361, 100001591, 89202186, 73156270, 91135137, 8995732, 18999294, 30619663, 81004067, 27000431, 50000921, 92034554, 10801175, 50002440, 56515472, 73002930, 91007629, 78078000, 18999294, 95028956, 81004067, 47280684, 43487889}));}
TEST(TC, TCC157) { EXPECT_EQ(311008031, MaximizingGCD::maximumGCDPairing({230003964, 220000402, 211004670, 119070000, 240480240, 14932388, 243177598, 91007629, 299999004, 232900001, 71188451, 179292960, 239819580, 78108030, 231231000, 79777031, 70527791, 67830433, 191938031, 100003361, 131715071, 121275000, 23164218, 187563671, 11009027, 296075643, 189733031, 123444360, 81004067, 287843813}));}
TEST(TC, TCC160) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({933024093, 960101392, 990812430, 933024093, 900157437, 994075754, 960101392, 972048804, 960101392, 910076290, 900209853, 900157437, 900014319, 972048804, 910076290, 960065776, 972048804, 950017499, 910076290, 972048804, 900014319, 844030436, 900157437, 900209853, 900188361, 900157437, 910076290, 822019606, 900157437, 900014319}));}
TEST(TC, TCC163) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({972048804, 900014319, 900014319, 900209853, 900014319, 972076764, 960101392, 960101392, 972048804, 960101392, 900014319, 900188361, 900030249, 972076764, 990687330, 822019606, 900014319, 933024093, 950017499, 900014319, 900063639, 844030436, 900014319, 972115644, 992143072, 960101392, 900014319, 900157437, 900014319, 900014319}));}
TEST(TC, TCC166) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({950041591, 994075754, 900014319, 910076290, 972076764, 900014319, 900209853, 844030436, 960101392, 960101392, 950041591, 992129312, 960065776, 900014319, 972076764, 910076290, 822019606, 976068944, 972054924, 900157437, 933029043, 972115644, 910076290, 972048804, 990687330, 950041591, 950041591, 972115644, 900014319, 972076764}));}
TEST(TC, TCC169) { EXPECT_EQ(3, MaximizingGCD::maximumGCDPairing({844030436, 900014319, 960101392, 900157437, 900126531, 900055917, 900209853, 910076290, 972048804, 990687330, 900030249, 900014319, 950041591, 933029043, 972076764, 950041591, 972076764, 960101392, 900014319, 900014319, 900055917, 972076764, 994064582, 992129312, 900209853, 990687330, 994075754, 933029043, 994075754, 972048804}));}
TEST(TC, TCC172) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({972076764, 972076764, 911007899, 900157437, 994075754, 900014319, 950041591, 972048804, 900126531, 900157437, 990687330, 960101392, 900014319, 960065776, 950041591, 933024093, 990687330, 900014319, 960101392, 900157437, 990687330, 994064582, 900014319, 900014319, 994075754, 900209853, 900063639, 960101392, 950017499, 972076764}));}
TEST(TC, TCC175) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({900209853, 972048804, 900016119, 972054924, 910076290, 900063639, 900014319, 900126531, 972048804, 994075754, 960065776, 933029043, 960101392, 910076290, 900014319, 990812430, 900209853, 900030249, 972076764, 994064582, 972076764, 950041591, 822019606, 960101392, 900157437, 910076290, 900209853, 910076290, 972076764, 933024093}));}
TEST(TC, TCC178) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({900055917, 972048804, 900014319, 900014319, 972076764, 822019606, 910076290, 822019606, 900157437, 900157437, 900014319, 900157437, 900055917, 933029043, 992129312, 900014319, 822019606, 950017499, 972048804, 960101392, 950041591, 900014319, 900126531, 900126531, 972076764, 933029043, 950041591, 960101392, 933029043, 933024093}));}
TEST(TC, TCC181) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({994075754, 844030436, 900157437, 900157437, 950041591, 900063639, 972076764, 990687330, 900188361, 994075754, 900014319, 900014319, 960101392, 992143072, 994075754, 900157437, 994075754, 910076290, 900014319, 960101392, 900014319, 960101392, 822019606, 972076764, 992143072, 972076764, 972048804, 992129312, 900188361, 900030249}));}
TEST(TC, TCC184) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({900209853, 900014319, 900014319, 900157437, 911007899, 972115644, 933024093, 844030436, 994075754, 900014319, 910076290, 990687330, 960101392, 910076290, 900014319, 994075754, 972076764, 844030436, 972048804, 900157437, 992143072, 960101392, 972048804, 900157437, 960101392, 972115644, 990687330, 900157437, 972048804, 960101392}));}
TEST(TC, TCC187) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({900030249, 960101392, 994075754, 960065776, 950041591, 900063639, 900014319, 972076764, 960101392, 900157437, 910076290, 950041591, 900014319, 900055917, 950041591, 994075754, 950041591, 972076764, 950041591, 960101392, 950041591, 972076764, 950041591, 900014319, 950041591, 900157437, 972048804, 990687330, 972115644, 972048804}));}
TEST(TC, TCC190) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({17082706, 2250363, 10339787, 76004569, 210905419, 12575258, 349962037, 2476862, 777554287, 299518777, 223323469, 3372394, 840442429, 280375483, 788598721, 2106974, 1993078, 46147445, 173919049, 674564701, 11591834, 42271, 529036369, 678235463, 909981911, 927170197, 18088358, 9539078, 12897058, 958573687}));}
TEST(TC, TCC193) { EXPECT_EQ(4, MaximizingGCD::maximumGCDPairing({371493827, 1479554, 217887337, 164753, 5391194, 2649238, 282042773, 7543498, 895724597, 122350831, 876111169, 644863127, 18734246, 446382691, 771199031, 18171782, 7611358, 2912666, 16725862, 787011623, 686792177, 17299822, 16028542, 571743071, 37737977, 1653758, 775249337, 791102833, 218421239, 998454143}));}
TEST(TC, TCC196) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({4811966, 126929983, 77834311, 872968937, 562132007, 370421941, 110314103, 802677653, 516402839, 12167798, 653910347, 69393151, 240194659, 25362591, 372423157, 755419433, 975549431, 576825103, 187907969, 904954613, 82444451, 202588153, 6733414, 311397917, 285080737, 762785207, 323260351, 14238542, 7892446, 81918797}));}
TEST(TC, TCC199) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({35119079, 111249059, 13015238, 450785591, 183656747, 6943502, 107435239, 17441026, 759991339, 564439607, 973666, 29126603, 847694567, 11765458, 708096317, 17529154, 7365854, 979130671, 8262946, 4496846, 659187677, 425048749, 444734, 50218057, 45440921, 486017963, 666059917, 389743531, 861430729, 8549822}));}
TEST(TC, TCC202) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({13380298, 355188611, 779161673, 788474831, 588856003, 212337329, 18026774, 10876738, 413823749, 360644033, 11383102, 309766, 594467999, 8707562, 8627338, 255866183, 464305799, 409689131, 116341333, 426541519, 5714806, 138017023, 485717819, 821680297, 538663469, 718841267, 665114959, 15515194, 4254134, 853052873}));}
TEST(TC, TCC205) { EXPECT_EQ(911007899, MaximizingGCD::maximumGCDPairing({843620967, 573873300, 1050192, 181681500, 804386924, 238484568, 499998096, 411009803, 115914713, 795093186, 861006978, 775805321, 285838924, 337134599, 106620975, 729326399, 44616460, 411642000, 499365899, 625168975, 782689415, 178378200, 909957707, 135202578, 67386932, 672523331, 732629699, 50000921, 866391439, 128318484}));}
TEST(TC, TCC208) { EXPECT_EQ(911007899, MaximizingGCD::maximumGCDPairing({607506900, 46203959, 261888315, 814356434, 129144722, 609896203, 11007637, 781863177, 649119584, 92076189, 137975721, 811006308, 830974560, 100001591, 81004067, 303500999, 100001591, 81690869, 811006308, 864803940, 80033339, 818931710, 301111696, 96651465, 829317030, 830003832, 900000262, 175819624, 773032178, 735188275}));}
TEST(TC, TCC211) { EXPECT_EQ(911007899, MaximizingGCD::maximumGCDPairing({908638641, 100014059, 14522961, 588588000, 681080400, 344356320, 98116072, 745029827, 566651579, 641458619, 91007629, 789452999, 100926000, 2369258, 795874499, 896484938, 812891827, 810081899, 121554900, 810993840, 165978072, 91007629, 322419899, 269549280, 820000270, 115133400, 242810911, 668196988, 229927499, 820000270}));}
TEST(TC, TCC214) { EXPECT_EQ(911007899, MaximizingGCD::maximumGCDPairing({251113640, 16502627, 55167360, 861006978, 861005710, 173020224, 894505272, 528425699, 126486360, 50000921, 875524650, 35483249, 855840539, 382582200, 50002189, 168648480, 81006397, 737987675, 356642568, 153342341, 757665558, 644096, 784521539, 554365331, 659894259, 830001502, 611341155, 910363803, 742359419, 299666744}));}
TEST(TC, TCC217) { EXPECT_EQ(911007899, MaximizingGCD::maximumGCDPairing({97804008, 567911903, 24177153, 641787300, 111464199, 758011196, 81004067, 813203891, 197495099, 642027371, 81006397, 269220599, 56156100, 268980528, 112142751, 830003832, 152996703, 854851799, 830001502, 810810000, 713512800, 100197899, 799543700, 810990406, 886830746, 798865148, 100017493, 343095996, 91007629, 820000270}));}
TEST(TC, TCC220) { EXPECT_EQ(1359352909, MaximizingGCD::maximumGCDPairing({911007899, 792330000, 770704844, 448345010, 648456795, 789365246, 613625626, 659875829, 448345010, 559426860, 567022909, 911007899, 569987663, 448345010, 529716868, 911007899, 448345010, 710896114, 799926049, 829636041, 911007899, 448345010, 763308342, 745727283, 588648065, 911007899, 596044567, 911007899, 448345010, 699477080}));}
TEST(TC, TCC223) { EXPECT_EQ(1150247134, MaximizingGCD::maximumGCDPairing({911007899, 239239235, 862761900, 659151867, 915674760, 911007899, 911007899, 657026370, 299737474, 850509660, 367389994, 239239235, 911007899, 827026200, 510137251, 493220764, 782857140, 239239235, 716756040, 433491094, 234572374, 491095267, 911007899, 452852836, 239239235, 323220934, 697394298, 640109883, 287485234, 239239235}));}
TEST(TC, TCC226) { EXPECT_EQ(1000142065, MaximizingGCD::maximumGCDPairing({89134166, 303919490, 498444241, 346869065, 525570936, 911007899, 746817676, 552378645, 529389372, 763533314, 911007899, 411554065, 950569620, 588588000, 470752693, 31639915, 236608751, 474571129, 377597065, 253324389, 447763420, 89134166, 653273000, 968502150, 501697824, 622545000, 696222575, 89134166, 49572445, 911007899}));}
TEST(TC, TCC229) { EXPECT_EQ(1042032610, MaximizingGCD::maximumGCDPairing({369684010, 507193550, 911007899, 806413800, 729008280, 448908854, 459832606, 624323700, 852273460, 131024711, 85577110, 313024330, 504123724, 235618810, 59300860, 417708910, 582175636, 540726796, 982731750, 539152802, 582200004, 502879808, 537908886, 501305814, 459856974, 672348600, 534839060, 189759150, 956455500, 593123756}));}
TEST(TC, TCC232) { EXPECT_EQ(1015343836, MaximizingGCD::maximumGCDPairing({555908750, 735570146, 626496727, 104335937, 104335937, 459435086, 650871391, 676095750, 911007899, 475965796, 911007899, 364472445, 552039875, 512140857, 528450620, 486893216, 911007899, 517069096, 463303961, 104335937, 208107880, 279773690, 498274740, 911007899, 104335937, 503202979, 807235956, 339248086, 539378040, 388847109}));}
TEST(TC, TCC235) { EXPECT_EQ(1999999927, MaximizingGCD::maximumGCDPairing({999999947, 999999988, 999999941, 999999931, 999999943, 999999984, 999999950, 999999933, 999999939, 999999983, 999999992, 999999942, 999999980, 999999988, 999999976, 999999939, 1000000000, 999999994, 999999985, 999999996, 999999930, 999999927, 999999944, 999999951, 999999935, 999999927, 999999986, 1000000000, 999999977, 999999997}));}
TEST(TC, TCC238) { EXPECT_EQ(1999999927, MaximizingGCD::maximumGCDPairing({999999982, 999999995, 999999949, 999999937, 999999989, 999999984, 999999931, 999999945, 999999983, 999999932, 999999994, 999999978, 999999951, 999999996, 999999938, 999999943, 999999980, 999999976, 999999952, 999999949, 999999929, 999999975, 999999978, 999999944, 999999998, 999999932, 999999933, 999999990, 999999995, 999999947}));}
TEST(TC, TCC241) { EXPECT_EQ(1999999943, MaximizingGCD::maximumGCDPairing({999999997, 999999978, 999999957, 999999990, 999999953, 999999961, 999999956, 999999959, 999999949, 999999967, 999999998, 999999987, 999999943, 999999992, 999999996, 999999951, 999999965, 999999945, 1000000000, 999999986, 999999943, 1000000000, 999999984, 999999994, 999999957, 999999947, 999999986, 999999982, 999999976, 999999946}));}
TEST(TC, TCC244) { EXPECT_EQ(1999976903, MaximizingGCD::maximumGCDPairing({999976903, 999999995, 999999994, 999976907, 999999997, 999999997, 999976903, 999999996, 999999998, 999976909, 999999992, 999976916, 999999993, 1000000000, 999976911, 999999994, 999976903, 999999996, 999999980, 999976908, 999976906, 999976906, 999999987, 999976905, 999976907, 999976909, 999976923, 1000000000, 999976910, 1000000000}));}
TEST(TC, TCC247) { EXPECT_EQ(1999976933, MaximizingGCD::maximumGCDPairing({999976955, 999999990, 999999990, 999976947, 999999998, 999999996, 999976937, 999999987, 999976946, 999976947, 1000000000, 999999977, 999976946, 999999978, 999999986, 999976956, 999976935, 999999979, 999976943, 999976953, 999999987, 999976933, 999999986, 999976954, 999999980, 999976943, 1000000000, 999976933, 999999978, 999976955}));}
TEST(TC, TCC250) { EXPECT_EQ(2000000000, MaximizingGCD::maximumGCDPairing({1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000}));}
TEST(TC, TCC253) { EXPECT_EQ(32769, MaximizingGCD::maximumGCDPairing({1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912}));}
TEST(TC, TCC256) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({245466381, 95275444, 974571474, 501830322, 409098738, 767110750, 845716950, 821115872, 10014810, 616716465, 787189167, 396768680, 322334813, 684259682, 880492499, 224048977, 253674535, 820965013, 115115462, 636600769, 950148345, 542314107, 340563072, 353673391, 438865739, 776088410, 217852623, 683309587, 680007057, 999337835}));}
TEST(TC, TCC259) { EXPECT_EQ(931170240, MaximizingGCD::maximumGCDPairing({465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120, 465585120}));}
TEST(TC, TCC262) { EXPECT_EQ(4, MaximizingGCD::maximumGCDPairing({1, 2, 3, 2}));}
TEST(TC, TCC265) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({999999103, 999999107, 999999113, 999999131, 999999137, 999999151, 999999163, 999999181, 999999191, 999999193, 999999197, 999999223, 999999229, 999999323, 999999337, 999999353, 999999391, 999999433, 999999487, 999999491, 999999503, 999999527, 999999541, 999999587, 999999599, 999999607, 999999613, 999999667, 999999677, 999999733}));}
TEST(TC, TCC268) { EXPECT_EQ(1999999971, MaximizingGCD::maximumGCDPairing({1000000000, 999999999, 999999998, 999999997, 999999996, 999999995, 999999994, 999999993, 999999992, 999999991, 999999990, 999999989, 999999988, 999999987, 999999986, 999999985, 999999984, 999999983, 999999982, 999999981, 999999980, 999999979, 999999978, 999999977, 999999976, 999999975, 999999974, 999999973, 999999972, 999999971}));}
TEST(TC, TCC271) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}));}
TEST(TC, TCC274) { EXPECT_EQ(2000000000, MaximizingGCD::maximumGCDPairing({1000000000, 1000000000}));}
TEST(TC, TCC277) { EXPECT_EQ(16, MaximizingGCD::maximumGCDPairing({30030, 39270, 46410, 72930, 102102, 170170}));}
TEST(TC, TCC280) { EXPECT_EQ(100, MaximizingGCD::maximumGCDPairing({100, 200, 300, 500, 1100, 700}));}
TEST(TC, TCC283) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 3}));}
TEST(TC, TCC286) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({1, 1, 2, 2, 2, 2}));}
TEST(TC, TCC289) { EXPECT_EQ(25, MaximizingGCD::maximumGCDPairing({175, 100, 100, 100, 75, 125}));}
TEST(TC, TCC292) { EXPECT_EQ(5, MaximizingGCD::maximumGCDPairing({1, 1, 1, 29, 49, 74}));}
TEST(TC, TCC295) { EXPECT_EQ(7, MaximizingGCD::maximumGCDPairing({1, 2, 3, 4, 5, 6}));}
TEST(TC, TCC298) { EXPECT_EQ(1, MaximizingGCD::maximumGCDPairing({848634385, 228201421, 175050341, 332379793, 491753299, 304230571, 317177144, 672973714, 577413553, 175890090, 251639562, 99311906, 467255939, 334278267, 227812544, 744439843, 164187297, 596504709, 859314135, 193944509, 441199942, 191660520, 323503737, 812417491, 759819063, 352732785, 1560303, 44976355, 175387696, 643497687}));}
TEST(TC, TCC301) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({3, 3, 3, 3, 3, 3, 3, 3, 3, 5}));}
TEST(TC, TCC304) { EXPECT_EQ(4, MaximizingGCD::maximumGCDPairing({2, 4, 8, 2, 4, 8, 2, 4, 8, 2, 4, 8, 2, 4, 8, 2, 4, 8, 2, 4, 8, 2, 4, 8, 2, 4, 8, 2, 4, 8}));}
TEST(TC, TCC307) { EXPECT_EQ(7, MaximizingGCD::maximumGCDPairing({52363599, 87186678, 407241764, 107700235, 901198878, 38153667, 536202041, 332197699, 852086619, 159662397, 337216658, 333796395, 245163353, 1670554, 436275794, 87613500, 597599465, 69876962, 315458974, 448321709, 905398653, 92764562, 142175065, 790071845, 21235975, 911150549, 573408086, 265321706, 837837645, 768794748}));}
TEST(TC, TCC310) { EXPECT_EQ(31, MaximizingGCD::maximumGCDPairing({30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));}
TEST(TC, TCC313) { EXPECT_EQ(50, MaximizingGCD::maximumGCDPairing({99, 101, 98, 102, 75, 125, 175, 275}));}
TEST(TC, TCC316) { EXPECT_EQ(2, MaximizingGCD::maximumGCDPairing({735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134300, 735134298, 735134299, 1, 1, 1}));}

