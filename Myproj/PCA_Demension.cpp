// PCA_Demension.cpp: implementation of the PCA_Demension class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Myproj.h"
#include "PCA_Demension.h"
#include <math.h>
#include <algorithm>
#include "MyprojDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PCA_Demension::PCA_Demension()
{
	
}

PCA_Demension::~PCA_Demension()
{

}

int PCA_Demension::covariance(vector<double> x,vector<double> y,double & result)
{
	double sum_temp=0;
	for (size_t i=0 ; i<x.size(); ++i)
	{
		sum_temp = sum_temp + x[i] * y[i];
	}
	result = sum_temp / x.size();   //������������ƫ����
	return 1;
}

int PCA_Demension::PCA_demension(vector<vector<double> > Feature_Data,vector<vector<double> > &trans_data)
{
	Cols = Feature_Data[0].size();
	//���������ֵ��
	vector<double> Mean_values(Feature_Data[0].size(),0);
	for (size_t j=0 ; j<Feature_Data[0].size() ; ++j)
	{
		double sum_temp = 0;
		for (size_t i = 0 ; i<Feature_Data.size(); ++i)
		{
			sum_temp = sum_temp + Feature_Data[i][j];
		}
		Mean_values[j] = sum_temp / Feature_Data.size();  //�����һ��Ϊ���ԣ����֣� Ҫ�ڱ�����˹�ɾ������
		double test=Mean_values[j];
	}

	//ȥ��ֵ����
	for (j=0; j<Feature_Data[0].size() ; ++j)
	{
		for (size_t i=0 ; i<Feature_Data.size() ; ++i)
		{
			trans_data[i][j]=Feature_Data[i][j];
			Feature_Data[i][j] = Feature_Data[i][j] - Mean_values[j];
		}

	}
	rule_num=Feature_Data.size();
	att_num=Feature_Data[0].size();


	//����ת��
	vector<vector<double> > trans(Feature_Data[0].size(),vector<double>(Feature_Data.size(),0));
	for (size_t i=0 ; i<Feature_Data[0].size() ; ++i)
	{
		for (size_t j=0 ; j<Feature_Data.size(); ++j)
		{
			trans[i][j]=Feature_Data[j][i];
		}
	}
	


	//��ȡЭ�������    �ڴ����⣡
	vector<vector<double> > covariance_Matrix(Cols,vector<double>(Cols,0));
	for (i=0; i<Feature_Data[0].size(); ++i)
	{
		for (j=0; j<Feature_Data[0].size(); ++j)
		{
			double result = 0;
			covariance(trans[i],trans[j],result);
			covariance_Matrix[i][j]=result;
		}
	}

	//�����ϵ��
	
	vector<double> temp_var1;
	vector<double> temp_var2;
//  vector<vector<double> > correlation(Cols,vector<double>(Cols,0));
	correlation.resize(Cols);     //ʹ��[][]�����ʼ��������
	for (int kk=0 ; kk<Cols; ++kk)
	{
		correlation[kk].resize(Cols);
	}

	double result_var=0;
	for (i=0 ; i<Cols ; ++i)
	{
		double test1=trans[i][2];
		int test2=trans[0].size();
		double test=Mean_values[i];
		for (j=0 ; j<Cols ; ++j)
		{		
 			stdm(trans[i],trans[j],result_var);
 			correlation[i][j]=covariance_Matrix[i][j]/result_var;
		}
	}
	
	return 1;
}

int PCA_Demension::stdm(vector<double> std_data1,vector<double> std_data2,double & result)
{
	double temp1=0;
	double temp2=0;
	double sum1=0;
	double sum2=0;
	vector<double> temp;
	for (size_t i=0 ; i<std_data1.size() ; ++i)
	{
		temp1=std_data1[i];
		temp1=pow(temp1,2);
		temp2=std_data2[i];
		temp2=pow(temp2,2);
		sum1=sum1+temp1;
		sum2=sum2+temp2;
	}
	sum1=sum1/std_data1.size();
	sum2=sum2/std_data2.size();
	sum1=sqrt(sum1);
	sum2=sqrt(sum2);
	result=sum1*sum2;
	
	temp.clear();
	return 1;
}

bool PCA_Demension::JacbiCor(double *pMatrix, int nDim, double *pdbVects, vector<vector<double> > &Fea_Vec, double *pdbEigenValues, double dbEps, int nJt)
{
	//�����洢���������ľ���E
	for (int i = 0; i<nDim; ++i)
	{
		pdbVects[i*nDim+i]=1.0f;
		for (int j=0 ; j<nDim; ++j)
		{
			if (i!=j)
			{
				 pdbVects[i*nDim+j]=0.0f;
			}
		}
	}

	int nCount = 0;  //��������
	while(1)
	{
		//��pMatrix�ķǶԽ������ҵ����Ԫ��
		double dbMax = pMatrix[1];  //dbMax�洢���ǶԽ���Ԫ��
		int nRow = 0;
		int nCol = 1;
		for (int i=0;i<nDim;i++)
		{
			for (int j=0;j<nDim;j++)
			{
				double d = fabs(pMatrix[i*nDim+j]);
				if ((i!=j) && (d>dbMax))
				{
					dbMax=d;
					nRow=i;
					nCol=j;
				}
			}
		}
		if (dbMax<dbEps)  //��������
		{
			break;
		}
		if (nCount>nJt)   //���������ﵽ����
		{
			break;
		}
		nCount++;
		double dbApp=pMatrix[nRow*nDim+nRow];
		double dbApq=pMatrix[nRow*nDim+nCol];
		double dbAqq=pMatrix[nCol*nDim+nCol];

		//������ת�Ƕ�
		double dbAngle = 0.5*atan2(-2*dbApq,dbAqq-dbApp);
		double dbSinTheta = sin(dbAngle);
		double dbCosTheta = cos(dbAngle);
		double dbSin2Theta = sin(2*dbAngle);
		double dbCos2Theta = cos(2*dbAngle);

		pMatrix[nRow*nDim+nRow] = dbApp * dbCosTheta * dbCosTheta +
			dbAqq * dbSinTheta * dbSinTheta + 2*dbApq*dbCosTheta*dbSinTheta;
		pMatrix[nCol*nDim+nCol] = dbApp * dbSinTheta * dbSinTheta +
			dbAqq * dbCosTheta * dbCosTheta - 2*dbApq*dbCosTheta*dbSinTheta;
		pMatrix[nRow*nDim+nCol] = 0.5 * (dbAqq-dbApp) * dbSin2Theta +dbApq*dbCos2Theta;
		pMatrix[nCol*nDim+nRow] = pMatrix[nRow*nDim+nCol];

		for (i = 0; i< nDim ;i++)
		{
			if ((i!=nCol) && (i!=nRow))
			{
				int u=i*nDim + nRow;
				int w=i*nDim + nCol;
				dbMax = pMatrix[u];
				pMatrix[u]=pMatrix[w]*dbSinTheta+dbMax*dbCosTheta;
				pMatrix[w]=pMatrix[w]*dbCosTheta+dbMax*dbSinTheta;
			}
		}
		
		for (int j = 0;j<nDim ;j++)
		{
			if ((j!=nCol) && (j!=nRow))
			{
				int u=nRow*nDim+j;
				int w=nCol*nDim+j;
				dbMax=pMatrix[u];
				pMatrix[u]=pMatrix[w]*dbSinTheta + dbMax * dbCosTheta;
				pMatrix[w]=pMatrix[w]*dbCosTheta - dbMax * dbSinTheta;
			}
		}

		//������������
		for ( i = 0;i<nDim; i++)
		{
			int u=i*nDim+nRow;
			int w=i*nDim+nCol;
			dbMax=pdbVects[u];
			pdbVects[u]=pdbVects[w]*dbSinTheta+dbMax*dbCosTheta;
			pdbVects[w]=pdbVects[w]*dbCosTheta-dbMax*dbSinTheta;
		}
	}//end while


	//������ֵ�������򲢰�����������������
	std::map<double,int> mapEigen;
	for ( i = 0; i< nDim; i++)
	{
		pdbEigenValues[i] = pMatrix[i*nDim+i];
		mapEigen.insert(make_pair(fabs(pdbEigenValues[i]),i));   //����ֵȡ����ֵ�������� 
	}

	double *pdbTmpVec = new double[nDim*nDim];
	vector<vector<double> > pdbTmpVec2(Fea_Vec.size(),vector<double>(Fea_Vec[0].size(),0));
	std::map<double,int>::reverse_iterator iter = mapEigen.rbegin(); //rbegin rend �������
	memset(jacbi_ord,0,nDim);
	for (int j=0 ; iter != mapEigen.rend(), j<nDim ; ++iter, ++j)
	{
		for ( i = 0; i<nDim ; ++i)
		{
			pdbTmpVec[i * nDim +j] = pdbVects[i* nDim + iter->second];
		}

		for (int mm=0 ; mm<Fea_Vec.size();mm++)
		{
			pdbTmpVec2[mm][j] = Fea_Vec[mm][iter->second];
		}
		//����ֵ��������
		pdbEigenValues[j] = iter->first;  //map��д���ʱ��ͻᰴ�������Ž��������Ĭ������
											//����������ֱ�Ӵӵ�һ����ʼ��ֵ�����ǰ�����ֵ��С��������
		jacbi_ord[j]=iter->second;
	}
	

	//�趨������
	for ( i=0; i<nDim; i++)
	{
		double dSumVec = 0;
		for ( j=0 ; j<nDim ;j++)
		{
			dSumVec += pdbTmpVec[j*nDim+i];
		}
		if (dSumVec<0)
		{
			for ( j=0;j<nDim;j++)
			{
				pdbTmpVec[j*nDim+i] *= -1;
			}
		}
	}

	memcpy(pdbVects,pdbTmpVec,sizeof(double)*nDim*nDim);
	delete []pdbTmpVec;

	//����������Ҳ��˳������
	for (i=0 ; i<Fea_Vec.size() ;i++)
	{
		for (j=0 ; j<nDim ;j++)
		{
			Fea_Vec[i][j]=pdbTmpVec2[i][j];
		}
	}
	
	return 1;
}

bool PCA_Demension::PCA_select(double *pdb_Vect, double *pdb_EigenValues, vector<vector<double> > &pdb_feature, int dbNum, double var, int *nvar, double *Final_Vect, double *Final_Eigen)
{
	double temp[100];
	double each_temp[100];
	memset(temp,0,dbNum);
	memset(each_temp,0,dbNum);
	double sum=0;
	for (int i = 0 ; i<dbNum ; ++i)
	{
		temp[i]=fabs(pdb_EigenValues[i]);
		sum=sum+temp[i];
		each_temp[i]=sum;
	}

	for (int p=0; p<dbNum ; ++p)
	{	
		if (each_temp[p]/sum >= var)
		{
			*nvar=p+1; //��0��ʼ����
			break;
		}
	}

	for ( i=0; i<*nvar*dbNum ;i++)
	{
		Final_Vect[i]=pdb_Vect[i];
	}

	pdb_feature[0].resize(*nvar);
	for ( i=0; i<pdb_feature.size(); i++)
	{
		for (int j=0; j<*nvar ; j++)
		{
			pdb_feature[i][j]=pdb_feature[i][j];
		}
		if (i<pdb_feature.size()-1)
		{
			pdb_feature[i+1].resize(*nvar);
		}
	}

	rule_num=pdb_feature.size();
	att_num=*nvar;
	return 1;

}

//�ϲ��ظ�Ԫ��
vector<double> PCA_Demension::unique(vector<double> vals)
{
	vector<double> unique_vals;
	vector<double>::iterator itr;
	vector<double>::iterator subitr;

	int flag = 0;
	while ( !vals.empty())
	{
		unique_vals.push_back(vals[0]);
		itr=vals.begin();
		subitr=unique_vals.begin() + flag;
		while ( itr != vals.end() )
		{
			if( *subitr == *itr)
			{
				itr = vals.erase(itr);
			}
			else
			{
				itr++;
			}
		}
		flag++;
	}
	return unique_vals;
}


double PCA_Demension::log2(double n)
{
	return log10(n) / log10(2.0) ;
}

//������Ϣ��
double PCA_Demension::compute_entropy(vector<double> v)
{
	vector<double> unique_v;
	unique_v = unique(v);
	
	vector<double>::iterator itr;
	itr = unique_v.begin();
	
	double entropy = 0.0;
	auto total=v.size();
	while (itr!=unique_v.end())
	{
		double cnt = count(v.begin(),v.end(),*itr);
		entropy -= cnt/total * log2(cnt / total);
		itr++;
	}
	return entropy;
}

//������Ϣ�����
vector<double> PCA_Demension::compute_gain(vector<vector<double> > truths)
{
	vector<double> gain(truths[0].size() - 1, 0);
	vector<double> attribute_vals;
	vector<double> vals_true;
	vector<double> labels;
	memset(mid,0,truths[0].size());
	for ( unsigned j=0 ; j< truths.size() ; j++)
	{
		labels.push_back(truths[j].back());
	}            //�õ������ǩ
	
 	double test22=truths.size();
	double test11=truths[0].size();
	for ( unsigned i=0 ; i<truths[0].size() -1 ; i++)      //�����truths�ж���������
	{
		for ( int j=0 ; j<truths.size() ; j++)
		{
			attribute_vals.push_back(truths[j][i]);        //�����i��������attribute_vals
			vals_true.push_back(truths[j][i]);
		}

		//��ֵ��ɢ��
		int idx[100];                     //������¼����
		memset(idx,0,truths.size());
		double temp,amin;

		for (j=0;j<truths.size();j++)
		{
			amin=attribute_vals[j];
			idx[j]=j;
			for ( int m=0;m<truths.size();m++)   //��ѡ��Ϊ�������ݴ�С�������򲢼�¼ԭ����
			{
				
				if (attribute_vals[m]<amin)
				{			
					amin=attribute_vals[m];
					idx[j]=m;
				}
			}
			vals_true[j]=attribute_vals[idx[j]];
			attribute_vals[idx[j]]=9999999;
		}					//������ֵ�������򣬲���¼����

		double test22=vals_true.size();
		vector<double> unique_vals = unique(vals_true);  //ȥ�ظ�ֵ
		double test=unique_vals.size();
		double vals_avg[1000];
		memset(vals_avg,0,unique_vals.size()-1);   //��ѡ���ֵ㼯��
		for ( j=0;j<unique_vals.size()-1;j++)      
		{
			vals_avg[j]=(unique_vals[j]+unique_vals[j+1])/2;  //��ֵ�����ѡ�ڵ�
		}
		
		//ȡ��Ϣ������С�ķֶε�j ����������ɢ��
		vector<double> subset0;
		vector<double> subset1;
		double gain_min=100;
		int idx_min=-1;
		for (j=0 ; j<unique_vals.size()-1;j++) 
		{
			for (unsigned k = 0; k<truths.size();k++)
			{
				if (vals_true[k] <= vals_avg[j])
				{
					subset0.push_back(truths[idx[k]].back());
				}
				else
				{	
					subset1.push_back(truths[idx[k]].back());
				}
			}
			double test=vals_avg[j];
			double A0 = subset0.size();
			double A1 = subset1.size();
			gain[i] = A0/truths.size() * compute_entropy(subset0) + A1/truths.size() * compute_entropy(subset1);
			double test2=gain[i];
			if (gain[i] < gain_min)
			{
				gain_min=gain[i];
				idx_min=j;
				B0=A0;
				B1=A1;
			}
			subset0.clear();
			subset1.clear();
		}			
		mid[i] = vals_avg[idx_min];
		gain[i] = (compute_entropy(labels) - gain_min)/ (-B0/truths.size()*log2(B0/truths.size())-B1/truths.size()*log2(B1/truths.size()));
		attribute_vals.clear();
		vals_true.clear();
		
	}
	return gain;
}

//������ֱ�Ӹ�gain�����
vector<double> PCA_Demension::compute_gain_ratio(vector<vector<double> > truths)
{
	 vector<double> gain = compute_gain(truths);
	 vector<double> entropies;
	 vector<double> gain_ratio;

	 for (unsigned i = 0; i<truths[0].size() -1; i++)
	 {
		 vector<double> attribute_vals(truths.size(),0);
		 for (unsigned j = 0;j<truths.size();j++)
		 {
			 attribute_vals[j]=truths[j][i];
		 }
		 double current_entropy = compute_entropy(attribute_vals);
		 if (current_entropy)
		 {
			 gain_ratio.push_back(gain[i] / current_entropy);
		 }
		 else
		 {
			 gain_ratio.push_back(0.0);
		 }
	 }
	 return gain_ratio;
}


//�ҳ����ݼ�����������ǩ
double PCA_Demension::find_most_common_label(vector<vector<double> > data)
{
	vector<double> labels;
	for (unsigned i = 0;i<data.size();i++)
	{
		labels.push_back(data[i].back());
	}

	vector<double>::iterator itr=labels.begin();
	double most_common_label;
	unsigned most_counter = 0;
	while (itr!=labels.end())
	{
		unsigned current_counter = count(labels.begin(),labels.end(),*itr);
		if (current_counter > most_counter)
		{
			most_common_label = * itr;
			most_counter = current_counter;
		}
		itr++;
	}
	return most_common_label;
}

//���������ҳ�����ȡֵ
vector<double> PCA_Demension::find_attribute_values(double attribute,vector<vector<double> > data)
{
	vector<double> values(0,data.size());
	for (unsigned i=0; i<data.size();i++)
	{
		if (data[i][attribute] <= mid[(int)attribute] )
		{
			values[i]=mid[(int)attribute];
		}
		else
			values[i]=1024;
	}
	return unique(values);
}


//��������ɾ����ѡ�������
vector<vector<double> > PCA_Demension::drop_one_attribute(double attribute,vector<vector<double> > data)
{
	vector<vector<double> > new_data(data.size(),vector<double>(data[0].size()-1,0));
	for (unsigned i = 0 ;i<data.size();i++)
	{
		data[i][attribute] = -1;  //���Ϊ-1���ʾ�ѿ��ǵ�����
	}
	return data;
}


void PCA_Demension::print_tree(Tree tree, int depth)
{
 	for ( int d = 0; d<depth ; d++)
	{
		printf("���\n ");
	}

	if(!tree.branches.empty())  //����Ҷ�ӽ��
	{
		printf("������: %d ",tree.root);
		for(int i=0;i<tree.branches.size();i++)
		{
			printf("��֦: %d ",i);
			for ( int d = 0; d<depth +1 ;d++)
			{
				printf(" depth ");
			}
			printf("��֧: %f\n",tree.branches[i]);  //��ʾΪ0��ԭ�����Թ�һ���������Ϊ������תΪint��Ϊ0
			print_tree(tree.children[i],depth+2);	
		}
	}
	else
	{
		printf("Ҷ�ӽ��: %d\n",tree.root);
	}
}

void PCA_Demension::build_decision_tree(vector<vector<double> > examples,Tree &tree)
{
	//�ж��Ƿ�����ʵ������ͬһ��
	vector<double> labels(examples.size(),0);
	for (unsigned i=0;i<examples.size();i++)
	{
		labels[i] = examples[i].back();
	}
	if (unique(labels).size() == 1)
	{
		tree.root = labels[0];
		return;
	}
	
	//�ж��Ƿ���ʣ������δ����
	if (count(examples[0].begin(),examples[0].end(),-1)== examples[0].size()-1)
	{
		tree.root=find_most_common_label(examples);
		return;
	}
	
	//������Ϣ����� ѡ�����������������Ϊ���ڵ� ���ҳ��ýڵ�����ȡֵ
 	vector<double> standard = compute_gain(examples);
	tree.root=0;
	for ( i = 0; i< standard.size(); i++)
	{
		if (standard[i] >= standard[tree.root] && examples[0][i] != -1)
		{
			tree.root = i;
		}
	}
//	tree.branches = find_attribute_values(tree.root,examples);


	//���ݽڵ�ȡֵ ��examples�ֳ������Ӽ�
	vector<vector<double> > new_examples = drop_one_attribute(tree.root,examples);
	vector<vector<double> > subset;
	vector<vector<double> > subset1;

	for (unsigned j=0;j<examples.size();j++)
	{
		if( examples[j][tree.root] <= mid[(int)tree.root])
		{
			subset.push_back(new_examples[j]);
		}
	}
	double temp=mid[tree.root];
	tree.branches.push_back(mid[tree.root]);

	//��ÿ���Ӽ��ݹ����build_decision_tree
	Tree new_tree;
	build_decision_tree(subset,new_tree);		
	tree.children.push_back(new_tree);
	subset.clear();


	for ( j=0;j<examples.size();j++)
	{		
		if( examples[j][tree.root] > mid[tree.root])
		{
			subset1.push_back(new_examples[j]);
		}
	}

	
	//������ڵ����������ɺ� Ī���������������mid[]ֵ�����仯�������б�û�����⣬ʲô������ֱ��c
									//�����ݴ���mid��ֵ����Ȼ�ܴ���������ܿ���!
	tree.branches.push_back(temp);

	//��ÿ���Ӽ��ݹ����build_decision_tree
	Tree new1_tree;
	build_decision_tree(subset1,new1_tree);
	tree.children.push_back(new1_tree);
	subset1.clear();
}
