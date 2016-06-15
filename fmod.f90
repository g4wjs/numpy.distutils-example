module fmod
  implicit none

  public :: fib, fib_calc

  private

  interface
     subroutine threaded_fib (a, n, fp) bind (C, name = 'threaded_fib')
       use, intrinsic :: iso_c_binding, only: c_float, c_int, c_funptr
       implicit none
       integer (c_int), value :: n
       real (kind=c_float), dimension (n), intent (out) :: a
       type (c_funptr), value :: fp
     end subroutine threaded_fib
  end interface

contains
  subroutine fib (a, n)
    use, intrinsic :: iso_c_binding, only: c_funptr, c_funloc

    implicit none
    integer, intent (in) :: n
    real, dimension (n), intent (out) :: a

    type (c_funptr) :: fp

    fp = c_funloc (fib_calc)
    call threaded_fib (a, n, fp)
  end subroutine fib

  subroutine fib_calc (a, n)
    implicit none
    integer, intent (in) :: n
    real, dimension (n), intent (out) :: a

    integer :: i

    do i = 1, n
       if (i .eq. 1) then
          a(i) = 0.D0
       else if (i .eq. 2) then
          a(i) = 1.D0
       else
          a(i) = a(i - 1) + a(i - 2)
       end if
    end do
  end subroutine fib_calc
end module fmod
