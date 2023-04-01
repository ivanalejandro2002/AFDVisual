
#include <iostream>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <fstream>
#define SCREENX 500
#define SCREENY 400
#define SENSIBILIDAD 900000
using namespace std;
void mezcla(long long int &semilla){
    semilla*=semilla;
    semilla+=rand()%1000000007;
    semilla%=1000000007;
}
int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    ifstream fin;
    ofstream fout;
    fin.open("AFD.in");
    fout.open("grafo.gv");
    fout<<"graph AFD{\n";
    int n; //cantidad denodos del autómata
    fin>>n;
    cout<<n<<"\n";
    string diccionario; //diccionario de letras, de tal forma que indexa a un elemento desde 0
    getline(fin,diccionario);

    getline(fin,diccionario); //leemos el diccionario
    vector<int> letras(256,0); //cubeta de elementos de diccionario para hacer el mapeo
    int i=0;
    for(char a:diccionario){
        if(letras[a]){
            cout<<"No puedes repetir dos veces una letra en el diccionario\n";
            return 0;
        }
        letras[a]=++i;
    }
    map<string, int > datos; //hasheo de elementos estado
    vector<bool> aceptacion(n+1);//estados de aceptacion
    vector<vector<int> > automata;
    automata.resize(n+1);
    string aux,adonde;
    for(i=1;i<=n;i++){
        automata[i].resize(diccionario.size()+1);
        fin>>aux;
        if(datos[aux]){
            cout<<"No puedes tener dos nodos con el mismo nombre\n";
            return 0;
        }
        datos[aux]=i;
    }
    int inicial, destino;
    for(i=0;i<n;i++){
        fin>>aux;
        cout<<aux<<"\n";
        if(!datos[aux]){
            cout<<"No existe el nodo :"<<aux<<"\n";
            return 0;
        }
        inicial = datos[aux];
        fout<<"\t"<<aux<<" -- {";
        for(int a=1;a<=diccionario.size();a++){
            fin>>adonde;
            destino =datos[adonde];
            if(!destino){
                cout<<"No existe el nodo :"<<adonde<<"\n";
                return 0;
            }
            automata[inicial][a]=destino;
            fout<<adonde;
            if(a<diccionario.size())fout<<",";
        }
        fout<<"}\n";
    }

    fout<<"}\n";
    fout.close();
    system("dot -Tjson grafo.gv -o foto.json");
    int k;
    fin>>k;
    cout<<k<<"\n";
    for(i=0;i<k;i++){
        fin>>aux;
        if(!datos[aux]){
            cout<<"No existe el nodo :"<<adonde<<"\n";
            return 0;
        }
        aceptacion[datos[aux]]=1;
    }
    int actual;
    fin>>aux;
    if(!datos[aux]){
        cout<<"No existe el nodo: "<<adonde<<"\n";
        return 0;
    }
    actual = datos[aux];
    string cad;
    fflush(stdin);
    getline(cin,cad);
    for(char co:cad){
        if(!letras[(int)co]){
            cout<<"La cadena no pertenece al diccionario\n";
            return 0;
        }
    }

    for(char co:cad){
        actual = automata[actual][letras[(int)co]];
    }
    if(aceptacion[actual]){
        cout<<"La cadena es valida\n";
    }else{
        cout<<"La cadena es invalida\n";
    }


    set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREENX,SCREENY,0,0);

    srand(time(NULL));
    int mapx,mapy;
    mapx=2000;
    mapy=2000;
    int r,g,b;
    long long int semilla;
    if(semilla<0)semilla*=-1;


    BITMAP *buffer = create_bitmap(mapx,mapy);
    clear_to_color(buffer,0x000000);
    for(int i=0;i<mapy/100;i++){
        for(int a=0;a<mapx/100;a++){
            r=(rand()+semilla)%255;
            mezcla(semilla);
            g=(rand()+semilla)%255;
            mezcla(semilla);
            b=(rand()+semilla)%255;
            mezcla(semilla);
            mapx=2000;
            mapy=2000;
            circlefill(buffer,50+i*100,50+a*100,38,r*256*256+g*256+b);
        }
    }
    blit(buffer, screen, 0, 0, 0, 0,SCREENX,SCREENY);
    int x,y,rad;
    x = 100;
    y=50;
    rad=38;
    int dir[2]={1,1};
    show_mouse(screen);

    /*while(!key[KEY_ESC]){
        clear_to_color(buffer,0x000000);
        if((x-r==0 && dir[0]==-1) || (x+r==500 && dir[0]==1))dir[0]*=-1;
        if((y-r==0 && dir[1]==-1) || (y+r==400 && dir[1]==1))dir[1]*=-1;
        circlefill(buffer,x,y,38,0xFF0000);
        blit(buffer,screen,0,0,0,0,500,400);
        x+=dir[0];
        y+=dir[1];
    }
    */

    int sx,sy;
    sx=sy=0;
    int restante=0;
    while(!key[KEY_ESC]){
        if(restante==0){
            if(key[KEY_W]){
                sy=max(0,sy-1);
                restante=SENSIBILIDAD;
            }
            if(key[KEY_S]){
                sy=min(mapy-SCREENY,sy+1);
                restante=SENSIBILIDAD;
            }
            if(key[KEY_A]){
                sx=max(0,sx-1);
                restante=SENSIBILIDAD;
            }
            if(key[KEY_D]){
                sx=min(mapx-SCREENX,sx+1);
                restante=SENSIBILIDAD;
            }
            blit(buffer,screen,sx,sy,0,0,SCREENX,SCREENY);
        }else{
            restante--;
        }
    }
}
END_OF_MAIN();
