/* This Source Code Form is subject to the terms of the BSD 2-Clause
 * License. If a copy of the this license was not distributed with this
 * file, you can obtain one from http://opensource.org/licenses/BSD-2-Clause. */

// Copyright 2014, Schmidt


#include "sbase.h"


// Print format for matrices.  Apologies for the ugliness
#define SBASE_MATPRINT_DEFAULT      0
#define SBASE_MATPRINT_MATLAB       1
#define SBASE_MATPRINT_DENSE        2
#define SBASE_MATPRINT_IMPL         3
#define SBASE_MATPRINT_INFO         4
#define SBASE_MATPRINT_INFO_DETAIL  5
#define SBASE_MATPRINT_COMMON       6
#define SBASE_MATPRINT_INDEX        7
#define SBASE_MATPRINT_SYMMODU      8
#define SBASE_MATPRINT_VTK          9
#define SBASE_MATPRINT_NATIVE       10
#define SBASE_MATPRINT_BASIC        11
#define SBASE_MATPRINT_LG           12
#define SBASE_MATPRINT_CONTOUR      13

SEXP sbase_petsc_matprinter_fmt(SEXP fmt)
{
  PetscErrorCode ierr = 0;
  
  switch (INT(fmt))
  {
  case SBASE_MATPRINT_DEFAULT:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_DEFAULT);
    break;
  case SBASE_MATPRINT_MATLAB:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_MATLAB);
    break;
  case SBASE_MATPRINT_DENSE:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_DENSE);
    break;
  case SBASE_MATPRINT_IMPL:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_IMPL);
    break;
  case SBASE_MATPRINT_INFO:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_INFO);
    break;
  case SBASE_MATPRINT_INFO_DETAIL:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_INFO_DETAIL);
    break;
  case SBASE_MATPRINT_COMMON:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_COMMON);
    break;
  case SBASE_MATPRINT_INDEX:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_INDEX);
    break;
  case SBASE_MATPRINT_SYMMODU:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_SYMMODU);
    break;
  case SBASE_MATPRINT_VTK:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_ASCII_VTK);
    break;
  case SBASE_MATPRINT_NATIVE:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_NATIVE);
    break;
  case SBASE_MATPRINT_BASIC:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_DRAW_BASIC);
    break;
  case SBASE_MATPRINT_LG:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_DRAW_LG);
    break;
  case SBASE_MATPRINT_CONTOUR:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_DRAW_CONTOUR);
    break;
  default:
    ierr = PetscViewerSetFormat(PETSC_VIEWER_STDOUT_WORLD, PETSC_VIEWER_DEFAULT);
    break;
  }
  
  RCHKERRQ(ierr);
  
  return RNULL;
}



SEXP sbase_petsc_matprinter(SEXP dim, SEXP ldim, SEXP data, SEXP row_ptr, SEXP col_ind)
{
  Mat mat;
  PetscErrorCode ierr;
  
  // Convert to PETSc storage
  mat = sbase_convert_rsparse_to_petscsparse(dim, ldim, data, row_ptr, col_ind);
  
  // Print
  MatView(mat, PETSC_VIEWER_STDOUT_WORLD);
  
  // destroy petsc matrix
  if (mat) {ierr = MatDestroy(&mat);RCHKERRQ(ierr);}
  
  return RNULL;
}

