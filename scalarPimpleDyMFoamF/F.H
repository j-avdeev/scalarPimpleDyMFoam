    List<scalar> nonDiag; // sums of non-diagonal elements

    nonDiag.resize(S.size());
    forAll(nonDiag, i)
    {
	nonDiag[i] = 0.0;
    }
	
    const lduAddressing& addr = SEqn.lduAddr();
    const labelList& lowerAddr = addr.lowerAddr();
    const labelList& upperAddr = addr.upperAddr();
	
    forAll(lowerAddr, i)
    {
// 	    A[lowerAddr[i]][upperAddr[i]] = pEqn.upper()[i];
// 	    A[upperAddr[i]][lowerAddr[i]] = pEqn.lower()[i];
	nonDiag[lowerAddr[i]] += SEqn.upper()[i];
	nonDiag[upperAddr[i]] += SEqn.lower()[i];
    }
	
    forAll(p.boundaryField(),I)
    {
	const fvPatch &ptch=S.boundaryField()[I].patch();
	forAll(ptch,J)
	{
	    int w=ptch.faceCells()[J];
	    nonDiag[w]+=SEqn.internalCoeffs()[I][J];
// // // 		Info << "nonDiag" << "[" << w << "]" << " = " << nonDiag[w]  << nl << endl;
	}
    
    }
	
// F = alpha1;
// 	forAll(p_rghEqn.diag(),i)
    forAll(SEqn.diag(),i)
    {

	      F[i] = SEqn.diag()[i]+nonDiag[i];
// 	F[i] = pEqn.diag()[i];
// 	      F[i] = abs(nonDiag[i]);
// 	      F[i] = abs(p_rghEqn.diag()[i])+abs(nonDiag[i]);
// 	      Info << "p_rghEqn.diag()[i]=" << p_rghEqn.diag()[i] << nl << endl;
// 	      Info << "UEqn.diag()=" << UEqn.diag() << nl << endl; 
    }

//     volScalarField absF
//     (
// 	"absF",
// 	mag(F)
//     );
//     absF.writeOpt() = IOobject::AUTO_WRITE;
//             tmagGradP.clear();
// 
//     F = absF;
    
//     volScalarField normalisedF
//     (
// 	"normalisedF",
// 	F/max(F)
//     );
//     normalisedF.writeOpt() = IOobject::AUTO_WRITE;
//     //         tmagGradP.clear();
// 
//     F = normalisedF; 
