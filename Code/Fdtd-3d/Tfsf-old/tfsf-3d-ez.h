void tfsf_3d_ez_init(double *hx,  double *hy, double *hz, 
		  double *ex,  double *ey,  double *ez, 
		  int first_x, int first_y, int first_z,
		  int last_x, int last_y, int last_z,
		  int size_x, int size_y, int size_z,
		  double che, double ceh,
		  double (*source)(double));

void tfsf_3d_ez(void);

