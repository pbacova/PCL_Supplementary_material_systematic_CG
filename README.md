# PCL_Supplementary_material_systematic_CG
Supplementary material for a paper describing a bottom-up approach for poly(caprolactone).
The material contains 

-the simulation data on the poly(caprolactone) (PCL) chains of various molecular weight in vacuum (directory vacuum) and in water (directory solvated) in Gromacs format

-the full description of the preparation of the systems and the simulation details (file supp_info.pdf) 

-the initial configuration of the PCL trimer prepared using the software AVOGADRO (file 3mer.gro in prepare directory)

-the code to multiply the trimer and create a fully extended chain of a desired length (file adjust_num_monomers_reducebond.c in prepare directory)

-the code to prepare the topology itp file for Gromacs for a desired chain using the combination of OPLS-AA and L-OPLS force field (file prepare_itp_pcl.c in prepare directory)

-the full list of the force field parameters with the comments about their origin (file supp_info.pdf) 

-the foce field parameters in the Gromacs format (file pcl_ff_final.itp in vacuum and in solvated directory)

-the comparison of the data obtained from the simulations in water with the data previously reported in literature (file supp_info.pdf)

 
