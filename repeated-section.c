//**********************// 
 //   Repeated section   //
//**********************// 

// Add new row in Gallery
Set(varNextID, Value(Last(ChargingCollection).CslNo) + 1);
Collect(
    ChargingCollection,
    {
        CslNo: Text(varNextID),
        CProjectCode: "",
        CBudgetHolder: "",
        CCostCode: "",
        CAmount: ""
    }
)

// Remove row from Gallery -----
RemoveIf(ChargingCollection,CslNo = ThisItem.CslNo)

// Sum repeated amount in the CostGallery 
Sum(ChargingGallery.AllItems,Amount)

// "Concatinate" joining the cells of individual rows first; then Concat added entires rows (output) in a single string named "ChargingCollectionRows"
UpdateContext({
    ChargingCollectionRows:
    Concat(
        ChargingGallery.AllItems,
        Concatenate(
            SlNo.Text,
            ";",
            ProjectCode.Text,
            ";",
            BudgetHolder.Text,
            ";",
            CostCode.Text,
            ";",
            Amount.Text,
            "|"
        )
    )
});

UpdateContext(
    {
        ChargingCollectionRows: Left(ChargingCollectionRows, Len(ChargingCollectionRows)-1)
    }
);

// Save in the SharePoint list
Patch(ProcLab, Defaults(ProcLab), {Title:DataCardValue23.Text, 'Approved Budget':DataCardValue28.Text, Charging:ChargingCollectionRows}) ;
Clear(ChargingCollectionRows);

// Show repeated table data "string" from SharePoint "Charging" field to the Apps screen
UpdateContext({
    strTableData: Gallery1.Selected.Charging
});
UpdateContext({arrRow: Split(strTableData, "|")});

ForAll(arrRow, 
Collect(AllRowItems,{
SlNo: Text(Last(FirstN(Split(Result,";").Result,1).Result).Result),
ProjectCode:Text(Last(FirstN(Split(Result,";").Result,2).Result).Result),
BudgetHolder:Text(Last(FirstN(Split(Result,";").Result,3).Result).Result),
CostCode:Text(Last(FirstN(Split(Result,";").Result,4).Result).Result),
Amount:Text(Last(FirstN(Split(Result,";").Result,5).Result).Result)}));
