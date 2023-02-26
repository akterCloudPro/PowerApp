//**********************// 
 //   Repeated section   //
//**********************// 

// Add new row in Gallery
Set(varNextID, Value(Last(SpecificationRepeatedRow).CitemNo) + 1);
Collect(
    SpecificationRepeatedRow,
    {
        CitemNo: Text(Last(SpecificationRepeatedRow).CitemNo + 1),
        CDescription: "",
        CSize: "",
        CQuantity: "",
        CUnitPricet: "",
        CAmount: ""
    }
);

// Remove row from Gallery -----
RemoveIf(SpecificationRepeatedRow,CitemNo = ThisItem.CitemNo)

// Sum repeated amount in the CostGallery 
Sum(SpecificationRepeatedRow.AllItems,CAmount)
 
Set(
    AllSpecificationsItemsString,
    Concat(
        galSpecifications.AllItems,
        Concatenate(
            inpItemNo.Text,
            ";",
            inpDescription.Text,
            ";",
            inpSize.Text,
            ";",
            inpQuantity.Text,
            ";",
            inpUnitPrice.Text,
            ";",
            inpTotalAmount.Text,
            "|"
        )
    )
);

ClearCollect( CollRepSecList, Patch(Procurement, Defaults(Procurement), {Title:DataCardValue1.Text, 'Requisition ID':DataCardValue11.Text, Specification:AllSpecificationsItemsString}) );

Set(varRepSecListID, First(CollRepSecList).'Requisition ID');

ForAll
(
    galSpecifications.AllItems,
    Patch
    (
        Procurement_Specifications, {Title:"", 'Request ID':varRepSecListID, Description:inpDescription.Text, 'Total Amount':inpAmount}
    )
);

Reset(galSpecifications);
ResetForm(formRequisition);
Navigate(scrMyRecords);


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
