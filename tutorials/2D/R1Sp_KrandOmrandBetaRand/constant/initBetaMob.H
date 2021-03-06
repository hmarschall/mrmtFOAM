#codeStream{


        code
        #{

            const IOdictionary& d = static_cast<const IOdictionary&>(dict);
            const fvMesh& mesh = refCast<const fvMesh>(d.db());

            //Create Field K
            volTensorField K
            (
                IOobject
                (
                    "K",
                    mesh.time().constant(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                ),
                mesh
            );

            scalarField k((1.0/3.0)*tr(K.internalField()));
            
            scalar minBeta(0.3);
            scalar maxBeta(0.6);
            
            scalar mink(min(k));
            scalar maxk(max(k));
            
            scalar slope
            (
                (
                    maxBeta - minBeta
                )
                /
                (
                    maxk - mink + small
                )
            );
            

            scalarField beta(slope*(k-mink) + minBeta);
            
            Info << endl << "\nout " << beta;

            writeEntry(os,beta);

        #};

        //- Optional:
        codeInclude
        #{
            #include "fvCFD.H"
            //#include <stdlib.h>
        #};

        //- Optional:
        codeOptions
        #{
            -I$(LIB_SRC)/finiteVolume/lnInclude \
            -I$(LIB_SRC)/meshTools/lnInclude
        #};


};
