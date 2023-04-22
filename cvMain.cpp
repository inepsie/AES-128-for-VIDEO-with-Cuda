typedef unsigned char INTTYPE;
#define NBKEY 11
#include <opencv2/opencv.hpp>
extern void cumain(unsigned char * k, unsigned int mode, unsigned char *hData, unsigned int width, unsigned int height, unsigned int Bpp);

using namespace cv;

INTTYPE rotWord(INTTYPE w){
	INTTYPE tmp;
	tmp = w & (255<<24);
	w = w << 8;
	w = w | tmp;
	return w;
}

INTTYPE subWord(INTTYPE w, INTTYPE * sb){
	INTTYPE res = 0;
	INTTYPE tmp;
	for(int i=0 ; i<4 ; ++i){
		tmp = w >> (8*(3-i));//On prend chacun des octets de tmp (de la gauche vers la droite).
		tmp = tmp & 255;
		tmp = sb[tmp];//On transforme ces octets via la sbox.
		res = res << (8*i) + tmp;//On construit le résultat en plaçant les nouveaux octets les uns à la suite des autres.
	}
	return res;
}

void keyExpansion(INTTYPE ** key_exp, INTTYPE * sb){
  srand(2);
	int w;
	INTTYPE * key_word = (INTTYPE *) malloc(11 * 4 * sizeof(*key_word));//On crée 11 clés formées de 4 mots de 32bits.
	INTTYPE r[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
	for(int i=0 ; i<4 ; ++i){
		key_word[i] = (INTTYPE) rand();
	}
	for(int i=4 ; i<(NBKEY-1)*4 ; ++i){
		key_word[i] = key_word[i-1];
		if(!(i%4)){
			key_word[i] = subWord(rotWord(key_word[i]), sb)  ^ r[i/4];	
		}
		key_word[i] ^= key_word[i-4];
	}
	for(int i=0 ; i<11 ; ++i){//On divise les clés crées dans des espaces de 8bits
		for(int j=0 ; j<4 ; ++j){
			w = key_word[i*4+j];//On prend chacun des mots de 32bits pour les diviser en 4;
			for(int h=0 ; h<4 ; ++h){
				(*key_exp)[i*16+j*4+h] = (w >> (3-h)) & 255;
			}
		}
	}
	free(key_word);
}

int main(int argc, char ** argv) {
  /*  AJOUT */
  INTTYPE sb[256] = {0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76 
        ,0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0 
        ,0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15
        ,0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75
        ,0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84
        ,0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf
        ,0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8
        ,0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2
        ,0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73
        ,0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb
        ,0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79
        ,0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08
        ,0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a
        ,0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e
        ,0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf
        ,0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16};
  INTTYPE * k = (INTTYPE *) malloc(11 * 16  * sizeof *k);
  keyExpansion(&k, sb);
  /*  AJOUT */
  VideoCapture cap;
  VideoWriter  out;
  if(argc != 4) {
    fprintf(stderr, 
	    "usage: %s <video_in_file | webcam> <out_file | screen>\n",
	    argv[0]);
    return 1;
  }
  /* déterminer l'entrée */
  if(strncmp(argv[1], "webcam", 6) == 0) {
    /* essayer d'ouvrir n'importe quelle caméra */
    cap.open(CV_CAP_ANY);
    /* si echec, quitte */
    if(!cap.isOpened()) return 2;
  } else {
    /* essayer d'ouvrir le fichier entrée vidéo */
    cap.open(argv[1]);
    /* si echec, quitte */
    if(!cap.isOpened()) return 3;
  }
  /* déterminer la sortie */
  if(strncmp(argv[2], "screen", 6) == 0) {
    namedWindow("cuCV", WINDOW_AUTOSIZE);
  } else {
    Size s(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    /* essayer d'initialiser le fichier sortie vidéo, si echec, quitte */
    if(!out.open(argv[2], CV_FOURCC('H','2','6','4'), 30, s)) return 4;
  }
  Mat frame, bgra;
  /* boucle principale */
  for(;;) {
    /* récupérer la frame courante */
    cap >> frame;
    /* si plus de frame, sortir */
    if(frame.empty()) break;
    assert(frame.channels() == 3);
    /* convertion de la frame en 32bits */
    //frame.convertTo(frame, CV_8UC3);
    /* appel du traitement en CUDA (simpleTexture.cu) */
    cumain(k, atoi(argv[3]),(unsigned char *)frame.data, frame.cols, frame.rows, frame.channels());
    /* afficher ou enregistrer l'image */
    if(out.isOpened()) {      
      out.write(frame);
    } else {
      imshow("cuCV", frame);
      /* attendre 10ms pour capture clavier, si echap alors break */
      if((waitKey(10) & 0xFF) == 27)
	break;
    }
  }
  return 0;
}

