#!/bin/bash
echo "Creando archivos de residuos..."

# Para HEM
echo "aas;HEM" > HEM_residuos.csv
echo "LYS;$(grep -c "LYS" HEM_A_LYS_CA.pdb)" >> HEM_residuos.csv
echo "ARG;$(grep -c "ARG" HEM_A_ARG_CA.pdb)" >> HEM_residuos.csv
echo "HIS;$(grep -c "HIS" HEM_A_HIS_CA.pdb)" >> HEM_residuos.csv
echo "GLU;$(grep -c "GLU" HEM_A_GLU_CA.pdb)" >> HEM_residuos.csv
echo "ASP;$(grep -c "ASP" HEM_A_ASP_CA.pdb)" >> HEM_residuos.csv

# Para GFP
echo "aas;GFP" > GFP_residuos.csv
echo "LYS;$(grep -c "LYS" GFP_A_LYS_CA.pdb)" >> GFP_residuos.csv
echo "ARG;$(grep -c "ARG" GFP_A_ARG_CA.pdb)" >> GFP_residuos.csv
echo "HIS;$(grep -c "HIS" GFP_A_HIS_CA.pdb)" >> GFP_residuos.csv
echo "GLU;$(grep -c "GLU" GFP_A_GLU_CA.pdb)" >> GFP_residuos.csv
echo "ASP;$(grep -c "ASP" GFP_A_ASP_CA.pdb)" >> GFP_residuos.csv

# Para ACE2
echo "aas;ACE2" > ACE2_residuos.csv
echo "LYS;$(grep -c "LYS" ACE2_A_LYS_CA.pdb)" >> ACE2_residuos.csv
echo "ARG;$(grep -c "ARG" ACE2_A_ARG_CA.pdb)" >> ACE2_residuos.csv
echo "HIS;$(grep -c "HIS" ACE2_A_HIS_CA.pdb)" >> ACE2_residuos.csv
echo "GLU;$(grep -c "GLU" ACE2_A_GLU_CA.pdb)" >> ACE2_residuos.csv
echo "ASP;$(grep -c "ASP" ACE2_A_ASP_CA.pdb)" >> ACE2_residuos.csv

ls *_residuos.csv
