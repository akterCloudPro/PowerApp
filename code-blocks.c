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

    

