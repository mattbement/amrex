#include <AMReX.H>
#include <AMReX_Print.H>
#include <AMReX_BaseFab.H>
#include <AMReX_ParmParse.H>
#include <AMReX_Utility.H>

using namespace amrex;

int main(int argc, char* argv[])
{
    amrex::Initialize(argc,argv);

    long iters = 0;
    int boxsize = 0;
    int ncomps = 0;

    {
        ParmParse pp;
        pp.get("iters", iters);
        pp.get("boxsize",boxsize);
        pp.get("ncomps", ncomps);
    }

        amrex::Print() << std::endl;

#ifdef AMREX_USE_GPU_PRAGMA
        amrex::Print() << "Fortran version of BaseFab testing suite." << std::endl;
#else
        amrex::Print() << "C++ version of BaseFab testing suite." << std::endl;
#endif
        amrex::Print() << "All results should equal 5.5. " << std::endl  
                       << "Cubic boxes of length: " << boxsize << std::endl
                       << "Number of components: " << ncomps << std::endl
                       << "Number of iterations of each test: " << iters << std::endl
                       << "=========================================" << std::endl << std::endl;

    // ====================================================================
    // SetVal
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);

        fab1.setVal(1.0);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.setVal(5.5);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::setVal() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ====================================================================

    // SetValIfNot {}

    // ====================================================================
    // Invert 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);

        fab1.setVal(2.0/5.5);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.invert(2, bx1, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::invert() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }
    // ====================================================================
    // Norm 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(5.5);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.norm(bx1, 1, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::norm() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }
    // ====================================================================

    // Norminfmask 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(5.5);

        Box bx2(IntVect(0), IntVect(boxsize-1));
        BaseFab<int> fab2(bx2,ncomps);
        fab2.setVal(0);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.norminfmask(bx1, fab2, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::norminfmask() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ====================================================================
    // Sum 
    {
        double timer;
        double total = 0;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(5.5/(bx1.numPts()*ncomps));

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           total = fab1.sum(bx1, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::sum() test." << std::endl
                       << "Result: " << total << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }
    // ===================================================================
    // plus 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(2.75);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2.75/iters);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.plus(fab2, bx2, bx1, 0, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::plus() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }
    // ===================================================================
    // minus 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(8.25);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2.75/iters);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.minus(fab2, bx2, bx1, 0, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::minus() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ===================================================================
    // mult & divide 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(5.5);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2.75);

        Box bx3(IntVect(10), IntVect(10+boxsize-1));
        BaseFab<Real> fab3(bx3,ncomps);
        fab3.setVal(2.75);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.mult(fab2, bx2, bx1, 0, 0, ncomps);
           fab1.divide(fab3, bx3, bx1, 0, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::mult() and BaseFab<Real>::divide() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/(iters/2.0) << " seconds/ops." << std::endl
                       << "                         or: " << double(iters)/(2*timer)   <<  " ops/second." << std::endl << std::endl; 
    }
    // ===================================================================
    // mult & protected_divide 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(5.5);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2.75);

        Box bx3(IntVect(10), IntVect(10+boxsize-1));
        BaseFab<Real> fab3(bx3,ncomps);
        fab3.setVal(2.75);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.mult(fab2, bx2, bx1, 0, 0, ncomps);
           fab1.protected_divide(fab3, bx3, bx1, 0, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::mult() and BaseFab<Real>::protected_divide() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/(iters/2.0) << " seconds/ops." << std::endl
                       << "                         or: " << double(iters)/(2*timer)   <<  " ops/second." << std::endl << std::endl; 
    }
    // ===================================================================
    // dot 
    {
        double timer;
        double total = 0;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(double(2.75)/(bx1.numPts()*ncomps));

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(double(2.0)/(bx2.numPts()*ncomps));

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           total = fab1.dot(bx1, 0, fab2, bx2, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::dot() test." << std::endl
                       << "Result: " << total  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }
    // ===================================================================
    // dotmask
    {
        double timer;
        double total = 0;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(2.75/(bx1.numPts()*ncomps));

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2/(bx2.numPts()*ncomps));

        Box bx3(IntVect(0), IntVect(boxsize-1));
        BaseFab<int> fab3(bx3,ncomps);
        fab3.setVal(1);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           total = fab1.dotmask(fab3, bx1, 0, fab2, bx2, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::dotmask() test." << std::endl
                       << "Result: " << total << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ===================================================================
    // saxpy 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(1);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2.25);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.saxpy(2, fab2, bx2, bx1, 0, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::saxpy() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ===================================================================
    // xpay 
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(2.25);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(1);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.xpay(2, fab2, bx2, bx1, 0, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::xpay() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ===================================================================
    // addproduct
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(-0.75);

        Box bx2(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2.5);

        Box bx3(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab3(bx3,ncomps);
        fab3.setVal(2.5);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.addproduct(bx1, 0, ncomps, fab2, 0, fab3, 0);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::addproduct() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ===================================================================
    // LinComb
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(1.0);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(2.0);

        Box bx3(IntVect(10), IntVect(10+boxsize-1));
        BaseFab<Real> fab3(bx3,ncomps);
        fab3.setVal(3.0);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.linComb(fab2, bx2, 0, fab3, bx3, 0, 0.5, 1.5, bx1, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::linComb() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ===================================================================
    // Copy
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(0.0);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(5.5);

        Vector<Real> buffer(bx1.numPts()*ncomps, 0.0);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.copy(fab2, bx2, 0, bx1, 0, ncomps);
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::copy() test." << std::endl
                       << "Result: " << fab1(IntVect::TheZeroVector())  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/iters << " seconds/iter." << std::endl
                       << "                         or: " << double(iters)/timer << " iters/second." << std::endl << std::endl; 
    }

    // ===================================================================
    // CopyToMem & CopyFromMem
    {
        double timer;

        Box bx1(IntVect(0), IntVect(boxsize-1));
        BaseFab<Real> fab1(bx1,ncomps);
        fab1.setVal(5.5);

        Box bx2(IntVect(1000), IntVect(1000+boxsize-1));
        BaseFab<Real> fab2(bx2,ncomps);
        fab2.setVal(0.0);

        Vector<Real> buffer(bx1.numPts()*ncomps, 0.0);

        timer = second();
        for (int i=0; i<iters; ++i)
        {
           fab1.copyToMem(bx1, 0, ncomps, buffer.data());
           fab2.copyFromMem(bx2, 0, ncomps, buffer.data());
        }
        timer = second() - timer;

        amrex::Print() << "BaseFab<Real>::copyToMem() and copyFromMem() test." << std::endl
                       << "Result: " << fab2(IntVect(1000))  << std::endl
                       << "Completed in: "                <<  timer << " seconds." << std::endl
                       << " or, completed at a rate of: " <<         timer/(iters/2.0) << " seconds/op." << std::endl
                       << "                         or: " << double(iters)/(2*timer)   << " ops/second." << std::endl << std::endl; 
    }
    // ===================================================================

    amrex::Finalize();
}
