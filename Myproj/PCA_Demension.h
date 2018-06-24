// PCA_Demension.h: interface for the PCA_Demension class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCA_DEMENSION_H__E566EB94_8679_4F61_B352_20B27E96EEFC__INCLUDED_)
#define AFX_PCA_DEMENSION_H__E566EB94_8679_4F61_B352_20B27E96EEFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
//#include <Eigen/Dense>

#endif // _MSC_VER > 1000

//using namespace Eigen;
//using Eigen::MatrixXd;
using namespace std;

typedef struct Tree{
	int root;
	vector<double> branches;
	vector<Tree> children;
};
class PCA_Demension  
{
public:
	int jacbi_ord[100];
	Tree tree;
	double mid[100];
	double B0;
	double B1;
	void build_decision_tree(vector<vector<double> > examples,PCA_Demension::Tree &tree);
	void print_tree(PCA_Demension::Tree tree,int depth);
	double log2(double n);
	bool PCA_select(double *pdb_Vect,double *pdb_EigenValues,vector<vector<double> > &pdb_feature,int dbNum,double var,int *nvar,double *Final_Vect,double *Final_Eigen);
	bool JacbiCor(double * pMatrix,int nDim,double * pdbVects,vector<vector<double> > &Fea_Vec,double *pdbEigenValues,double dbEps,int nJt);
	int Cols;
	vector<vector<double> > correlation;
	int stdm(vector<double> std_data1,vector<double> std_data2,double & result);
	int PCA_demension(vector<vector<double> > Feature_Data,vector<vector<double> > &trans_data);
	int covariance(vector<double> x,vector<double> y,double & result);
	PCA_Demension();
	virtual ~PCA_Demension();

	string decision_tree_name;
	unsigned att_num;
	unsigned rule_num;

	vector<double> unique(vector<double> vals);
	double compute_entropy(vector<double> v);
	vector<double> compute_gain(vector<vector<double> > truths);
	vector<double> compute_gain_ratio(vector<vector<double> > truths);
	double find_most_common_label(vector<vector<double> > data);
	vector<double> find_attribute_values(double attribute,vector<vector<double> > data);
	vector<vector<double> > drop_one_attribute(double attribute,vector<vector<double> > data);
//	void build_decision_tree(vector<vector<double> > examples,Tree &tree);
	
};

#endif // !defined(AFX_PCA_DEMENSION_H__E566EB94_8679_4F61_B352_20B27E96EEFC__INCLUDED_)
