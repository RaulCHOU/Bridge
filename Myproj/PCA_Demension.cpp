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
	result = sum_temp / x.size();   //不采用样本无偏估计
	return 1;
}

int PCA_Demension::PCA_demension(vector<vector<double> > Feature_Data,vector<vector<double> > &trans_data)
{
	Cols = Feature_Data[0].size();
	//求个特征均值先
	vector<double> Mean_values(Feature_Data[0].size(),0);
	for (size_t j=0 ; j<Feature_Data[0].size() ; ++j)
	{
		double sum_temp = 0;
		for (size_t i = 0 ; i<Feature_Data.size(); ++i)
		{
			sum_temp = sum_temp + Feature_Data[i][j];
		}
		Mean_values[j] = sum_temp / Feature_Data.size();  //如果第一行为属性（汉字） 要在表格中人工删除改行
		double test=Mean_values[j];
	}

	//去均值处理
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


	//矩阵转置
	vector<vector<double> > trans(Feature_Data[0].size(),vector<double>(Feature_Data.size(),0));
	for (size_t i=0 ; i<Feature_Data[0].size() ; ++i)
	{
		for (size_t j=0 ; j<Feature_Data.size(); ++j)
		{
			trans[i][j]=Feature_Data[j][i];
		}
	}
	


	//求取协方差矩阵    内存问题！
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

	//求相关系数
	
	vector<double> temp_var1;
	vector<double> temp_var2;
//  vector<vector<double> > correlation(Cols,vector<double>(Cols,0));
	correlation.resize(Cols);     //使用[][]必须初始化行列数
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
	//构建存储特征向量的矩阵E
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

	int nCount = 0;  //迭代次数
	while(1)
	{
		//在pMatrix的非对角线上找到最大元素
		double dbMax = pMatrix[1];  //dbMax存储最大非对角线元素
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
		if (dbMax<dbEps)  //精度满足
		{
			break;
		}
		if (nCount>nJt)   //迭代次数达到上限
		{
			break;
		}
		nCount++;
		double dbApp=pMatrix[nRow*nDim+nRow];
		double dbApq=pMatrix[nRow*nDim+nCol];
		double dbAqq=pMatrix[nCol*nDim+nCol];

		//计算旋转角度
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

		//计算特征向量
		for ( i = 0;i<nDim; i++)
		{
			int u=i*nDim+nRow;
			int w=i*nDim+nCol;
			dbMax=pdbVects[u];
			pdbVects[u]=pdbVects[w]*dbSinTheta+dbMax*dbCosTheta;
			pdbVects[w]=pdbVects[w]*dbCosTheta-dbMax*dbSinTheta;
		}
	}//end while


	//对特征值进行排序并按序重排列特征向量
	std::map<double,int> mapEigen;
	for ( i = 0; i< nDim; i++)
	{
		pdbEigenValues[i] = pMatrix[i*nDim+i];
		mapEigen.insert(make_pair(fabs(pdbEigenValues[i]),i));   //特征值取绝对值进行排序 
	}

	double *pdbTmpVec = new double[nDim*nDim];
	vector<vector<double> > pdbTmpVec2(Fea_Vec.size(),vector<double>(Fea_Vec[0].size(),0));
	std::map<double,int>::reverse_iterator iter = mapEigen.rbegin(); //rbegin rend 逆向遍历
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
		//特征值重新排列
		pdbEigenValues[j] = iter->first;  //map在写入的时候就会按照索引号进行升序的默认排序
											//所以在这里直接从第一个开始赋值，就是按特征值由小到大排序
		jacbi_ord[j]=iter->second;
	}
	

	//设定正负号
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

	//让特征向量也按顺序排列
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
			*nvar=p+1; //从0开始计数
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

//合并重复元素
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

//计算信息熵
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

//计算信息增益比
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
	}            //得到分类标签
	
 	double test22=truths.size();
	double test11=truths[0].size();
	for ( unsigned i=0 ; i<truths[0].size() -1 ; i++)      //传入的truths有多少列属性
	{
		for ( int j=0 ; j<truths.size() ; j++)
		{
			attribute_vals.push_back(truths[j][i]);        //导入第i列属性至attribute_vals
			vals_true.push_back(truths[j][i]);
		}

		//数值离散化
		int idx[100];                     //排序后记录索引
		memset(idx,0,truths.size());
		double temp,amin;

		for (j=0;j<truths.size();j++)
		{
			amin=attribute_vals[j];
			idx[j]=j;
			for ( int m=0;m<truths.size();m++)   //简单选择法为该列数据从小到大排序并记录原索引
			{
				
				if (attribute_vals[m]<amin)
				{			
					amin=attribute_vals[m];
					idx[j]=m;
				}
			}
			vals_true[j]=attribute_vals[idx[j]];
			attribute_vals[idx[j]]=9999999;
		}					//将属性值进行排序，并记录索引

		double test22=vals_true.size();
		vector<double> unique_vals = unique(vals_true);  //去重复值
		double test=unique_vals.size();
		double vals_avg[1000];
		memset(vals_avg,0,unique_vals.size()-1);   //候选划分点集合
		for ( j=0;j<unique_vals.size()-1;j++)      
		{
			vals_avg[j]=(unique_vals[j]+unique_vals[j+1])/2;  //均值计算候选节点
		}
		
		//取信息增益最小的分段点j 将该属性离散化
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

//不用了直接跟gain结合了
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


//找出数据集中最多的类别标签
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

//根据属性找出可能取值
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


//从数据中删除已选择的属性
vector<vector<double> > PCA_Demension::drop_one_attribute(double attribute,vector<vector<double> > data)
{
	vector<vector<double> > new_data(data.size(),vector<double>(data[0].size()-1,0));
	for (unsigned i = 0 ;i<data.size();i++)
	{
		data[i][attribute] = -1;  //标记为-1则表示已考虑的属性
	}
	return data;
}


void PCA_Demension::print_tree(Tree tree, int depth)
{
 	for ( int d = 0; d<depth ; d++)
	{
		printf("深度\n ");
	}

	if(!tree.branches.empty())  //不是叶子结点
	{
		printf("属性名: %d ",tree.root);
		for(int i=0;i<tree.branches.size();i++)
		{
			printf("树枝: %d ",i);
			for ( int d = 0; d<depth +1 ;d++)
			{
				printf(" depth ");
			}
			printf("分支: %f\n",tree.branches[i]);  //显示为0的原因是以归一化后的数据为索引，转为int皆为0
			print_tree(tree.children[i],depth+2);	
		}
	}
	else
	{
		printf("叶子结点: %d\n",tree.root);
	}
}

void PCA_Demension::build_decision_tree(vector<vector<double> > examples,Tree &tree)
{
	//判断是否所有实例属于同一类
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
	
	//判断是否有剩余属性未考虑
	if (count(examples[0].begin(),examples[0].end(),-1)== examples[0].size()-1)
	{
		tree.root=find_most_common_label(examples);
		return;
	}
	
	//计算信息增益比 选择增益比最大的属性作为根节点 并找出该节点所有取值
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


	//根据节点取值 将examples分成两个子集
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

	//对每个子集递归调用build_decision_tree
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

	
	//这里根节点的左子树完成后 莫名其妙的右子树的mid[]值发生变化，可是判别没有问题，什么鬼东西简直了c
									//这里暂存了mid的值，虽然很蠢，但结果很快乐!
	tree.branches.push_back(temp);

	//对每个子集递归调用build_decision_tree
	Tree new1_tree;
	build_decision_tree(subset1,new1_tree);
	tree.children.push_back(new1_tree);
	subset1.clear();
}
