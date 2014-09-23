#include<GLUT/GLUT.h>

int xi[] = {0,-60,0,70,0,0};
int yi[] = {-80,30,90,-10,0,-80};
int xmin = -50,ymin=-50,xmax=50,ymax=50;

void init(void){
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320,320,-240,240);

}


typedef struct vertex{

	int x;
	int y;

};

int inside(vertex p, char edge){
	if(edge=='L')
		if(p.x>=xmin)
			return 1;
	else if(edge=='R')
		if(p.x<=xmax)
			return 1;
	else if(edge=='B')
		if(p.y>=ymin)
			return 1;
	else if(edge=='T')
		if(p.y<=ymax)
			return 1;
	return 0;

}

vertex intersect (vertex s,vertex p,char edge){

	float m = (p.y-s.y)/(p.x-s.x);
	if(edge=='L')
		if(inside(p,'L')&&!(inside(s,'L'))){
			s.x = xmin;
			s.y=s.y+m*(s.x-xmin);
			return s;
		}else if(inside(s,'L')&&!(inside(p,'L'))){
			
			p.x = xmin;
			p.y = p.y+m*(p.x-xmin);			
			return s;
		}
	else if(edge=='R')
		if(inside(s,'R')&&!(inside(p,'R'))){

			p.x=xmax;
			p.y=p.y+m*(xmax-p.x);
			return p;
		}else if(!inside(s,'R')&&(inside(p,'R'))){
			s.x=xmax;
			s.y=s.y+m*(xmax-s.x);
			return s;
		}
	else if(edge=='B')
		if(inside(p,'L')&&!(inside(s,'L'))){
			s.y=ymin;
			s.x = s.x+(1/m)*(s.y-ymin);
			return s;
		}else if(inside(s,'L')&&!(inside(p,'L'))){

			p.y=ymin;
			p.x = p.x+(1/m)*(p.y-ymin);
			return s;		

		}
	else
		if(inside(s,'B')&&!(inside(p,'B'))){
		
			p.y=ymax;
			p.x = p.x+(1/m)*(ymax-p.y);
			return p;

		}else if(!inside(s,'B')&&(inside(p,'B'))){
		
			s.y = ymax;
			s.x = s.x+(1/m)*(ymax-s.y);
			return s;
		
		}		

}
void clip(vertex in[],vertex out[],int Lin,int Lout){

	Lout = 0;
	vertex s,p,i;
	char clipEdge[] = {'L','R','B','T'};
	int k=0,j;
	s = in[Lin-1];
	for(k=0;k<4;k++){
	
		Lout = 0;
		for(j=0;j<Lin;j++){
		
			p = in[j];
			if(inside(p,clipEdge[k])){
					
				if(inside(s,clipEdge[k])){
					out[Lout++]=p;
				}else{
					
					i = intersect(s,p,clipEdge[k]);
					out[Lout++] = i;
					out[Lout++] = p;
	
				}
	
		
			}
			else if(inside(s,clipEdge[k])){
				i = intersect(s,p,clipEdge[k]);
				out[Lout++] = i;
			}
			s = p;
		
		}
		in = out;
		Lin = Lout;
		
	}
	glBegin(GL_POLYGON);
		glVertex2i(out[0].x,out[0].y);
		glVertex2i(out[1].x,out[1].y);
		glVertex2i(out[2].x,out[2].y);
		glVertex2i(out[3].x,out[3].y);
		glVertex2i(out[4].x,out[4].y);
	glEnd();
	glFlush();

}

void display(){

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2i(xi[0],yi[0]);
			glVertex2i(xi[1],yi[1]);
			glVertex2i(xi[1],yi[1]);
			glVertex2i(xi[2],yi[2]);
			glVertex2i(xi[2],yi[2]);
			glVertex2i(xi[3],yi[3]);
			glVertex2i(xi[3],yi[3]);
			glVertex2i(xi[4],yi[4]);
			glVertex2i(xi[4],yi[4]);
			glVertex2i(xi[5],yi[5]);
		glEnd();
		glFlush();

}

void myKey(unsigned char key, int x, int y){
	if(key=='c'){

		vertex ri[5],r0[5];int i;
	for(int i=0;i<5;i++){
		
		ri[i].x = xi[i];
		ri[i].y = yi[i];
		
	}
		glFlush();
		glBegin(GL_LINES);
		glVertex2i(-50,-50);	
		glVertex2i(-50,50);
		glVertex2i(-50,50);
		glVertex2i(50,50);
		glVertex2i(50,50);
		glVertex2i(50,-50);
		glVertex2i(50,-50);
		glVertex2i(-50,-50);
		
		glEnd();
		clip(ri,r0,5,0);
		glFlush();	
	}
}

int main(int argc,char ** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Clipping");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKey);
	init();
	glutMainLoop();
	return 0;


}
