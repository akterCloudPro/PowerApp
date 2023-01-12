// Reset Form, Set New Form, Navigate to another screen (Screen5) with Transition 
ResetForm(Form3);
NewForm(Form3);
Navigate(Screen5, ScreenTransition.Fade);

// Date Difference
DateDiff(DataCardValue4.SelectedDate,DataCardValue5.SelectedDate)

// Date Difference (Conditional)
If(
    And(
        IsBlank(DataCardValue4),
        IsBlank(DataCardValue5)
    ),
    0, 
    DateDiff(
        DataCardValue4.SelectedDate,
        DataCardValue5.SelectedDate
    ) + 1
)

// Data Field Visibility  (Conditional field data) 
If(
    DataCardValue8.Selected.Value = "Medical Leave",
    true,
    false
)

// Height (Conditional based on Attachment Section's visibility)
If(
    Attachments_DataCard1.Visible,
    671 + Attachments_DataCard1.Height,
    671
)

// Filed Visibility (Conditional Form mode)
If(
    Form3.Mode = FormMode.New,
    false,
    true
)


// (Collection) On Change - Department to relavent Approvers dropdown
Clear(ApproverManager);
Reset(DataCardValue3);
ClearCollect(
    FilteredApprovers,
    Filter(
        Approver,
        Title = DataCardValue2.Selected.Value
    )
);
ForAll(FilteredApprovers, Collect(ApproverManager, {
    Value: Approver.DisplayName,
    DisplayName: Approver.DisplayName,
    Email: Approver.Email,
    Picture: Approver.Picture,
    Claims: Approver.Claims,
    Department: Approver.Department,
    JobTitle: Approver.JobTitle
}));
    
// Save and Cancel Button (OnSelect)
SubmitForm(Form3); 
ResetForm(Form3); Navigate(Screen1); ScreenTransition.Fade;

// On Success (Form)
Notify("Your form has been submitted", NotificationType.Success);
Navigate(Screen1, ScreenTransition.Fade);

// Static Collection
ClearCollect(
    Header,
    {
        Reason: "Reason",
        Requester: "Requester",
        Days: "# of Days",
        Manager: "Manager",
        Status: "Status",
        Action: "Action"
        
    }
)

    // TemplateFill on Selection in Gallery item
If(ThisItem.IsSelected,RGBA(101, 96, 99, 0.15),RGBA(101,96,99,0))

//Edit Item (OnSelected)
Set(SelectedListItem, ThisItem); EditForm(Form3); Navigate(Screen5, ScreenTransition.Cover)
// In form3, set Itam = SelectedListItem


// GalleryRepeatingTable

// ---- Combine table data into one string variable and Save (Patch) in SharePoint ----

Set(
    AllItemsString,
    Concat(
        GalleryRepeatingTable.AllItems,
        Concatenate(
            SlNo.Text,
            ";",
            Name.Text,
            ";",
            PhoneNo.Text,
            ";",
            Email.Text,
            ";",
            City.Text,
            "|"
        )
    )
);

Patch(
    'Repeating Table',
     Defaults('Repeating Table'),
    {Title:Text(Today()),AllItems:AllItemsString }
    )


// ---- Add new row in Gallery ----

Collect(CollItems,{CItemSerialNumber: Text(Last(CollItems).CItemSerialNumber + 1) ,CVisitorName:"",CVisitorPhone:"",CVisitorEmail:"",CVisitorCity:""})

// ---- Remove Row from Gallery -----

RemoveIf(CollItems,CItemSerialNumber = ThisItem.CItemSerialNumber)

// ---- Pull data and generate collection object -----

Clear(CollItems); 
Set(AllItemsString,Left(AllItemsString, Len(AllItemsString)-1)); 
ForAll(Split(AllItemsString,"|"), 
Collect(CollItems,
{CItemSerialNumber: Text(Last(FirstN(Split(Result,";").Result,1).Result).Result),
CVisitorName:Text(Last(FirstN(Split(Result,";").Result,2).Result).Result),
CVisitorPhone:Text(Last(FirstN(Split(Result,";").Result,3).Result).Result),
CVisitorEmail:Text(Last(FirstN(Split(Result,";").Result,4).Result).Result),
CVisitorCity:Text(Last(FirstN(Split(Result,";").Result,5).Result).Result)}))


// Calculate Sum from repeated row 
Sum(GalleryRepeatingTable.AllItems,PhoneNo)
    
//Login Form (on Click Login button)
If(
    !IsBlank(
        LookUp(
            'User Credentials',
            UName = TextInput5.Text And Pwd = TextInput6.Text
        ).Title
    ),
    Navigate(Screen4),
    UpdateContext({ShowForgetMessage: true})
)
// Above ShowForgetMessage variable is for Showing error message in failed attempt (You have entered wrong user name or password)


    

