#define _USE_MATH_DEFINES 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <windows.h>
#include"product.h"

#define width_id 4
#define width_name 14
#define width_category 10
#define width_cost 14

Product items[MAXSIZE];
char* categories[] = {
	"水果蔬菜", "肉类禽蛋", "海鲜水产", "乳制品", "面包糕点",
	"饮料", "休闲零食", "罐头食品", "冷冻食品", "粮", "油", "调味",
	"个人护理", "家居清洁", "宠物用品", "婴儿用品", "酒水", "烟草"
};
int length = 0;

void MainMenu() {  //初始化首页面
	printf("------超市信息管理系统------\n");
	printf("1.客户\n");
	printf("2.管理员\n");
	printf("3.退出系统\n");
	printf("----------------------------\n");
	printf("选择你要进入的系统:");
	int chioce = 0;
	do {
		scanf("%d", &chioce);
		switch (chioce) {
		case 1:

			break;
		case 2:
			AdMenu();
			return;
			break;
		}
	} while (chioce != 3);
}

void AdMenu() {  //管理员菜单
	int chioce = 0;
	do {
		printf("1.添加商品\n");
		printf("2.删除商品\n");
		printf("3.修改商品信息\n");
		printf("4.查询商品\n");
		printf("5.显示所有商品\n");
		printf("6.返回主菜单\n");
		printf("7.关闭\n");
		printf("选择你要进入的系统:");
		scanf("%d", &chioce);
		switch (chioce) {
		case 1:
			Append();
			break;
		case 2:
			Delete();
			break;
		case 3:
			Modify();
			break;
		case 4:
			Find();
			break;
		case 5:
			Show();
			break;
		case 6:
			MainMenu();
			return;
			break;
		}
	} while (chioce != 7);
	return;
}

void save_data() {
	FILE* fp = fopen("products.txt", "w");
	if (fp == NULL) {
		printf("无法打开文件:stock.txt");
		return;
	}
	for (int i = 0; i < length; i++) {
		fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", items[i].id, items[i].name,
			items[i].category, items[i].cost_price, items[i].selling_price, items[i].stock,
			items[i].min_stock, items[i].max_stock, items[i].supplier, items[i].production_date,
			items[i].expiry_days);
	}
	fclose(fp);

}

void load_data() {
	FILE* fp = fopen("products.txt", "r");
	if (fp == NULL) {
		printf("无法打开文件:stock.txt");
		return;
	}
	while (length < MAXSIZE && fscanf(fp, "%d,%49[^,],%29[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%49[^,],%10[^,],%d\n", &items[length].id, items[length].name,
		items[length].category, items[length].cost_price, items[length].selling_price, items[length].stock,
		items[length].min_stock, items[length].max_stock, items[length].supplier, items[length].production_date,
		&items[length].expiry_days) == 11) {
		length++;
	}
	fclose(fp);
}

void Show() {
	if (length == 0) {
		printf("暂无商品\n");
		return;
	}

	printf("\n---所有商品信息---\n");
	printf("%-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s\n",
		width_id, "id", width_name, "名称", width_category, "分类",
		width_cost, "成本", width_cost, "售价", width_name, "库存",
		width_name + 4, "最小库存预警", width_name + 4, "最大库存容量",
		width_name, "供应商", width_name + 4, "生产日期", width_category, "保质期(天)");

	for (int i = 0; i < length; i++) {
		printf("%-*d  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*d\n",
			width_id, items[i].id,
			width_name, items[i].name,
			width_category, items[i].category,
			width_cost, items[i].cost_price,
			width_cost, items[i].selling_price,
			width_name, items[i].stock,
			width_name + 4, items[i].min_stock,
			width_name + 4, items[i].max_stock,
			width_name, items[i].supplier,
			width_name + 4, items[i].production_date,
			width_category, items[i].expiry_days);
	}
	printf("\n");
}

void Show_category_AD() {

	system("cls");

	int count = sizeof(categories) / sizeof(categories[0]);

	for (int i = 0; i < count; i++) {
		printf("\n---%s---\n",categories[i]);
		printf("%-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s\n",
			width_id, "id", width_name, "名称", 
			width_cost, "成本", width_cost, "售价", width_name, "库存",
			width_name + 4, "最小库存预警", width_name + 4, "最大库存容量",
			width_name, "供应商", width_name + 4, "生产日期", width_category, "保质期(天)");
		for (int j = 0; j < length; j++) {
			if (!strcmp(items[j].category, categories[i])) {  //类型相同
				printf("%-*d  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*d\n",
					width_id, items[j].id,
					width_name, items[j].name,
					width_cost, items[j].cost_price,
					width_cost, items[j].selling_price,
					width_name, items[j].stock,
					width_name + 4, items[j].min_stock,
					width_name + 4, items[j].max_stock,
					width_name, items[j].supplier,
					width_name + 4, items[j].production_date,
					width_category, items[j].expiry_days);
			}
		}
	}
	printf("\n");
}

void Show_category_CU() {
	int count = sizeof(categories) / sizeof(categories[0]);
	int lable = 0;
	int chioce;


	for (int i = 0; i < count; i++) {
		printf("%d.%s\n", i + 1, categories[i]);
	}
	printf("选择商品类别(按0返回上一级)：");
	scanf("%d", &chioce);

	for (int i = 0; i < count; i++) {
		if (lable == 1) break;
		if (i == chioce - 1) {
			lable = 1;
			printf("\n---%s---\n", categories[i]);
			printf("%-*s  %-*s  %-*s  %-*s  %-*s  %-*s\n",
				width_id, "id", width_name, "名称",width_cost, "售价",width_name, "供应商",
				width_name + 4, "生产日期", width_category, "保质期(天)");
			for (int j = 0; j < length; j++) {
				if (!strcmp(items[j].category, categories[i])) {
					printf("%-*d  %-*s  %-*s  %-*s  %-*s  %-*d\n",
						width_id, items[j].id,
						width_name, items[j].name,
						width_cost, items[j].selling_price,
						width_name, items[j].supplier,
						width_name + 4, items[j].production_date,
						width_category, items[j].expiry_days);
				}
			}
		}
	}


}

void Append() {  //向顺序表中添加商品
	system("cls");
	Product newproduct;
	printf("请输入商品id：");  //商品的id只能唯一，此处需要判断新加入的商品id是否与之前已加入的商品id相同
	scanf("%d", &newproduct.id);
	printf("请输入商品名称：");
	scanf("%s", newproduct.name);
	printf("请输入商品分类：");
	scanf("%s", newproduct.category);
	printf("请输入商品成本价格：");
	scanf("%s", newproduct.cost_price);
	printf("请输入商品销售价格：");
	scanf("%s", newproduct.selling_price);
	printf("请输入商品当前库存容量：");
	scanf("%s", newproduct.stock);
	printf("请输入商品最小库存预警值：");
	scanf("%s", newproduct.min_stock);
	printf("请输入商品最大库存容量：");
	scanf("%s", newproduct.max_stock);
	printf("请输入商品供应商信息：");
	scanf("%s", newproduct.supplier);
	printf("请输入商品生产日期：");
	scanf("%s", newproduct.production_date);
	printf("请输入商品保质期：");
	scanf("%d", &newproduct.expiry_days);

	items[length] = newproduct;

	length++;
	save_data();
	printf("添加成功\n");
	printf("\n");
}

void Delete() {  //根据id删除商品
	system("cls");
	int pos = 0;
	int id;
	printf("请输入您要删除的商品的id：");
	scanf("%d", &id);
	while (items[pos].id != id) {
		pos++;
		if (pos >= length) {
			printf("无此id的商品\n");
			return;
		}
	}
	for (int i = pos; i < length; i++) {
		items[i] = items[i + 1];
	}
	length--;
	save_data();
	printf("删除成功\n");
}

void Modify() {
	int pos = 0;
	int id;
	printf("请输入您要修改的商品的id：");
	scanf("%d", &id);
	while (items[pos].id != id) {
		pos++;
		if (pos >= length) {
			printf("无此id的商品\n");
			return;
		}
	}
	int chioce;
	do {
		printf("1.商品id\n");
		printf("2.商品名称\n");
		printf("3.商品分类\n");
		printf("4.成本价格\n");
		printf("5.销售价格\n");
		printf("6.当前库存容量\n");
		printf("7.最小库存预警值\n");
		printf("8.最大库存容量\n");
		printf("9.供应商信息\n");
		printf("10.生产日期\n");
		printf("11.保质期\n");
		printf("12.退出\n");
		printf("选择你要修改的项目:");
		scanf("%d", &chioce);
		switch (chioce) {
		case 1:
			printf("请输入新的商品id：");
			scanf("%d", &items[pos].id);
			break;
		case 2:
			printf("请输入新的商品名称：");
			scanf("%s", items[pos].name);
			break;
		case 3:
			printf("请输入新的商品分类：");
			scanf("%s", items[pos].category);
			break;
		case 4:
			printf("请输入新的商品成本价格：");
			scanf("%", items[pos].cost_price);
			break;
		case 5:
			printf("请输入新的商品销售价格：");
			scanf("%s", items[pos].selling_price);
			break;
		case 6:
			printf("请输入新的商品库存容量：");
			scanf("%s", items[pos].stock);
			break;
		case 7:
			printf("请输入新的商品最小库存预警：");
			scanf("%s", items[pos].min_stock);
			break;
		case 8:
			printf("请输入新的商品最大库存容量：");
			scanf("%s", items[pos].max_stock);
			break;
		case 9:
			printf("请输入新的供应商信息：");
			scanf("%s", items[pos].supplier);
			break;
		case 10:
			printf("请输入新的商品生产日期：");
			scanf("%s", items[pos].id);
			break;
		case 11:
			printf("请输入新的商品保质期：");
			scanf("%d", &items[pos].expiry_days);
			break;
		}
	} while (chioce != 12);

	save_data();
}

void Find() {
	int pos = 0;
	int id;
	printf("请输入您要查找的商品的id：");
	if (scanf("%d", &id) == 0) {
		while (getchar() != '\n');
		printf("无效输入\n");
		return;

	}
	while (items[pos].id != id) {
		pos++;
		if (pos >= length) {
			printf("无此id的商品\n");
			return;
		}
	}
	printf("\n---此商品信息---\n");

	printf("%-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s\n",
		width_id, "id", width_name, "名称", width_category, "分类",
		width_cost, "成本", width_cost, "售价", width_name, "库存",
		width_name + 4, "最小库存预警", width_name + 4, "最大库存容量",
		width_name, "供应商", width_name + 4, "生产日期", width_category, "保质期(天)");

	printf("%-*d  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*d\n",
		width_id, items[pos].id,
		width_name, items[pos].name,
		width_category, items[pos].category,
		width_cost, items[pos].cost_price,
		width_cost, items[pos].selling_price,
		width_name, items[pos].stock,
		width_name + 4, items[pos].min_stock,
		width_name + 4, items[pos].max_stock,
		width_name, items[pos].supplier,
		width_name + 4, items[pos].production_date,
		width_category, items[pos].expiry_days);
	printf("\n");
}

void Find_by_name_AD() {
	char str[MAX_NAME_LENGTH];
	int lable = 0;
	printf("请输入您要查找的商品的名称：");
	scanf("%s", str);
	for (int i = 0; i < length; i++) {
		if (!strcmp(items[i].name, str)) {
			lable = 1;
			printf("\n---此商品信息---\n");
			printf("%-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s\n",
				width_id, "id", width_name, "名称", width_category, "分类",
				width_cost, "成本", width_cost, "售价", width_name, "库存",
				width_name + 4, "最小库存预警", width_name + 4, "最大库存容量",
				width_name, "供应商", width_name + 4, "生产日期", width_category, "保质期(天)");
			printf("%-*d  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*s  %-*d\n",
				width_id, items[i].id,
				width_name, items[i].name,
				width_category, items[i].category,
				width_cost, items[i].cost_price,
				width_cost, items[i].selling_price,
				width_name, items[i].stock,
				width_name + 4, items[i].min_stock,
				width_name + 4, items[i].max_stock,
				width_name, items[i].supplier,
				width_name + 4, items[i].production_date,
				width_category, items[i].expiry_days);
		}
	}

	if (lable == 0) {
		printf("无此名称的商品\n");
	}

	printf("\n");

}

void Find_by_name_CU() {
	char str[MAX_NAME_LENGTH];
	int lable = 0;
	printf("请输入您要查找的商品的名称：");
	scanf("%s", str);
	for (int i = 0; i < length; i++) {
		if (!strcmp(items[i].name, str)) {
			lable = 1;
			printf("\n---此商品信息---\n");
			printf("%-*s  %-*s  %-*s  %-*s  %-*s  %-*s\n",
				width_id, "id", width_name, "名称", width_cost, "售价", width_name, "供应商",
				width_name + 4, "生产日期", width_category, "保质期(天)");
			printf("%-*d  %-*s  %-*s  %-*s  %-*s  %-*d\n",
				width_id, items[i].id,
				width_name, items[i].name,
				width_cost, items[i].selling_price,
				width_name, items[i].supplier,
				width_name + 4, items[i].production_date,
				width_category, items[i].expiry_days);
		}
	}

	if (lable == 0) {
		printf("无此名称的商品\n");
	}

	printf("\n");

}

Product* Find_by_id(int id) {
	int pos = 0;
	while (items[pos].id != id) {
		pos++;
		if (pos >= length) {
			printf("无此id的商品\n");
			return NULL;
		}
	}
	return &items[pos];
}
